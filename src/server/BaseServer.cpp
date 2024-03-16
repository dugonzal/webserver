/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 18:45:46 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"

BaseServer::BaseServer(void): opt(1) {
  ::bzero(&addr, sizeof(addr));
}

BaseServer::BaseServer(const BaseServer &copy): \
  serverFd(copy.serverFd), opt(copy.opt), addrLen(copy.addrLen) { }

BaseServer &BaseServer::operator=(const BaseServer &copy) {
  if (this != &copy) {
    addr = copy.addr;
    addrLen = copy.addrLen;
    serverFd = copy.serverFd;
    data = copy.data;
    opt = copy.opt;
    error_page = copy.error_page;
    buffer = copy.buffer;
    if (options && copy.options) // Only if the two have data inside
        *options = *(copy.options);
    else // Depending on copy.options, NULL or copy.options.
        options = copy.options ? new int(*copy.options) : nullptr;
  }
  return (*this);
}

BaseServer::~BaseServer(void) {
  close(serverFd);
}

void   BaseServer::setServerSide( void ) {
  opt = 1;
  if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     throw std::logic_error("socket creation failed");

  assert((serverFd > 2) && (serverFd < 6553));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(host.c_str());
  addrLen = sizeof(addr);

  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR,
    &opt, sizeof(opt)) < 0)
      throw std::logic_error(strerror(errno));
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEPORT,
    &opt, sizeof(opt)) < 0)
      throw std::logic_error(strerror(errno));
  int rc = fcntl(serverFd, O_NONBLOCK, (char *)&opt);
  if (rc < 0)
  {
    perror("ioctl() failed");
    close(serverFd);
    exit(-1);
  }
  if (bind(serverFd, (sockaddr *)&addr, addrLen) <  0)
    throw std::logic_error(strerror(errno));
  if (listen(serverFd, 1024) < 0)
    throw std::logic_error("listen failed");
}

void  BaseServer::setClientSide( void ) {
  timeout.tv_sec = 5; // 5 seconds for Client
  timeout.tv_usec = 0;
  bzero(clientMsg, sizeof(clientMsg));
  if ((clientFd = accept(serverFd, (sockaddr *)&clientAddr, &addrClientLen)) < 0)
    throw std::logic_error("error: accept");

  if (setsockopt(clientFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
      throw(std::runtime_error("error: setsockopt()"));
  
  int returnedBytes = recv(clientFd, clientMsg, sizeof(clientMsg), 0);
  if (returnedBytes < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) { // No data available, handle accordingly (e.g., retry later)
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
          std::cout << "No data available, retry later." << std::endl;
      } else { // Other error occurred
          close(serverFd);
          close(clientFd);
          throw std::logic_error("recv error");
      }
  } else if (returnedBytes == 0) { // Connection closed by the client
      close(serverFd);
      close(clientFd);
      throw std::runtime_error("client closed connection");
  } else // Data received, process it
      std::cout << "Bytes received: " << returnedBytes << std::endl;

  serverResponse = "HTTP/1.1 200  OK\r\n\r\n <html><head></head><body><h1 text-family=\"Roboto\" align=\"center\"> Hello, Inception42! </h1></body></html>";
  std::string msgRet(clientMsg);
  if (msgRet.find("favicon.ico", 0) != std::string::npos) {
    msgRet = readFaviconFile("resources/favicon.ico");
    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
    httpResponse += "Content-Type: image/x-icon\r\n";
    httpResponse += "Content-Length: " + std::to_string(msgRet.size()) + "\r\n";
    httpResponse += "\r\n";
    httpResponse += msgRet;
    send(clientFd, httpResponse.data(), httpResponse.size(), 0);
  }
  else
    send(clientFd, serverResponse.data(), serverResponse.size(), 0);
  
  close(clientFd); // After server has replied, close connection
  std::cout << clientMsg << std::endl;
  timeout.tv_sec = 30; // 30 seconds for select()
}

int   BaseServer::getSocket(void) const { return (serverFd); }

int   BaseServer::getNServers( void ) const { return (nServers); }

bool   BaseServer::checkServer( void ) const {
  if (port <= 0 || server_name.empty())
    return false;
  return true;
}

void   BaseServer::setServerNumber( int _amount ) {
  this->nServers = _amount;
}

void BaseServer::setPort( int _port ) {
  port = _port;
}

void BaseServer::setHost( std::string& _host ) {
  host = _host;
}

void  BaseServer::setServerName( std::string& _name ) {
  this->server_name = _name;
}

std::ostream &operator<<(std::ostream &os, const BaseServer &copy) {
  int ret = copy.getSocket();
  os << "host: " << ret << std::endl;
  return (os);
}
