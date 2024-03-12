/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/12 15:49:31 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"

BaseServer::BaseServer(void): serverFd(-42), opt(1), addrLen(sizeof(addr)), port(-1)  {
  ::bzero(&addr, sizeof(addr));
  memset(clientMsg, 0, sizeof(clientMsg));
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
    wConnections = copy.wConnections;
    error_page = copy.error_page;
    buffer = copy.buffer;
    if (options && copy.options) // Only if the two have data inside
        *options = *(copy.options);
    else // Depending on copy.options, NULL or copy.options.
        options = copy.options ? new int(*copy.options) : nullptr;
  }
  return (*this);
}

BaseServer::~BaseServer(void) { ::close(serverFd); }

int BaseServer::setServer(void) {
  setServerSide();
  setSelect();
  setClientSide();
  close(serverFd);

  // memset(clientMsg, 0, sizeof(clientMsg));
  return (serverFd);
}

void   BaseServer::setServerSide( void ) {
  if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     throw std::logic_error("socket creation failed");

  assert((serverFd > 2) && (serverFd < 6553));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(this->port);
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");

  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR,
    &opt, sizeof(opt)) < 0)
      throw std::logic_error(strerror(errno));

  if (bind(serverFd, (sockaddr *)&addr, addrLen) <  0)
    throw std::logic_error(strerror(errno));

/*   int rc = ioctl(serverFd, FIONBIO, (char *)&opt);
  if (rc < 0)
  {
    perror("ioctl() failed");
    close(serverFd);
    exit(-1);
  } */

  if (listen(serverFd, this->wConnections) < 0)
    throw std::logic_error("listen failed");
}

void  BaseServer::setSelect( void ) {
  FD_ZERO(&cSockets);
	FD_SET(serverFd, &cSockets);
	while (true) {
		rSockets = cSockets;

		std::cout << "Arrived before-select" << std::endl;
		if (select(FD_SETSIZE, &rSockets, NULL, NULL, NULL) < 0) { // Waits until file descriptor has info
			perror("error: select");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < FD_SETSIZE; i++) { // Check every file descriptor
			if (FD_ISSET(i, &rSockets)) { // True if 'i' has the same file descriptor as 'rSockets'
				if (i == serverFd) {
					setClientSide();
					FD_SET(clientFd, &cSockets);
          std::cout << clientMsg << std::endl;
				}
			}
			else {
				FD_CLR(i, &cSockets);
			}
		}
	}
}

void  BaseServer::setClientSide( void ) {
  if ((clientFd = accept(serverFd, (sockaddr *)&clientAddr, &addrClientLen)) < 0)
    throw std::logic_error("error: accept");
  timeout.tv_sec = 3; // 10 segundos
  timeout.tv_usec = 0;

  if (setsockopt(clientFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
      throw(std::runtime_error("error: setsockopt()"));
  if (recv(clientFd, clientMsg, sizeof(clientMsg) - 1, 0) <= 0) {
    close(serverFd);
    close(clientFd);
    throw std::logic_error("recv failed");
  }

  serverResponse = "HTTP/1.1 200  OK\r\n\r\n <html><head></head><body><h1 text-family=\"Roboto\" align=\"center\"> Hello, Inception42! </h1></body></html>";
  send(clientFd, serverResponse.data(), serverResponse.size(), 0);
  
  close(clientFd); // After server has replied, close connection
}

int   BaseServer::getSocket(void) const { return (serverFd); }

bool   BaseServer::checkServer( void ) const {
  if (this->port <= 0 || this->server_name.empty())
    return false;
  return true;
}

void BaseServer::setWConnections( int _amount ) {
  this->wConnections = _amount;
}

void BaseServer::setPort( int _port ) {
  this->port = _port;
}

void  BaseServer::setServerName( const std::string& _sName ) {
  this->server_name = _sName;
}

std::ostream &operator<<(std::ostream &os, const BaseServer &copy) {
  os << "host: " << copy.getSocket() << std::endl;
  return (os);
}
