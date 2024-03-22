/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/22 15:16:23 by jaizpuru         ###   ########.fr       */
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
        options = copy.options ? new int(*copy.options) : NULL;
  }
  return (*this);
}

BaseServer::~BaseServer(void) {
//  close(serverFd);
}

void   BaseServer::setServerSide( void ) {
  if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     throw std::logic_error("socket creation failed");

  cout << "socketFd: " << serverFd << endl;
  assert((serverFd > 2) && (serverFd < 6553));
  addr.sin_family = AF_INET;
  std::cout << "Port : " << port << std::endl;
  addr.sin_port = htons(port);
  std::cout << "Host : " << host << std::endl;
  std::cout << "Server name : " << server_name << std::endl << std::endl;
  addr.sin_addr.s_addr = inet_addr(host.c_str());
  addrLen = sizeof(addr);

/*   if (fcntl(serverFd, O_NONBLOCK, (char *)&opt) < 0) { // Valid for MacOS
    close(serverFd);
    std::cout << strerror(errno) << std::endl;
    throw std::logic_error("error: socket bind().");
  } */
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR,
    &opt, sizeof(opt)) < 0)
      throw std::logic_error("error: socket SO_REUSEADDR.");
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEPORT,
    &opt, sizeof(opt)) < 0)
      throw std::logic_error("error: socket SO_REUSEADDR.");
  if (bind(serverFd, (sockaddr *)&addr, addrLen) < 0) {
    std::cout << strerror(errno) << std::endl;
    throw std::logic_error("error: socket bind().");
  }
  if (listen(serverFd, 1024) < 0)
    throw std::logic_error("listen failed");
}

void  BaseServer::setRequest( void ) {
  Request client(serverFd);
}

int   BaseServer::getSocket(void) const { return (serverFd); }

int   BaseServer::getNServers( void ) const { return (nServers); }

bool   BaseServer::checkServer( void ) const {
  if (port <= 0 || server_name.empty())
    return false;
  return true;
}

void   BaseServer::setServerNumber(int _amount) {
  this->nServers = _amount;
}

void BaseServer::setPort(int _port) {
  port = _port;
}

void BaseServer::setHost(std::string& _host) {
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
