/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/12 23:21:07 by jaizpuru         ###   ########.fr       */
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

BaseServer::~BaseServer(void) {
  for (int i = 0; i < nServers; i++)
    close(serverFd[i]);
}

int BaseServer::setServer(void) {
  serverFd = new int[nServers];
  addr = new sockaddr_in[nServers];
  addrLen = new socklen_t[nServers];

  for (int i = 0; i < nServers; i++)
    setServerSide(i);
  setSelect();
  for (int i = 0; i < nServers; i++)
    close(serverFd[i]);

  // memset(clientMsg, 0, sizeof(clientMsg));
  return (0);
}

void   BaseServer::setServerSide( int _pos ) {
  if ((serverFd[_pos] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     throw std::logic_error("socket creation failed");

  assert((serverFd[_pos] > 2) && (serverFd[_pos] < 6553));
  addr[_pos].sin_family = AF_INET;
  addr[_pos].sin_port = htons(portAr[_pos]);
  addr[_pos].sin_addr.s_addr = inet_addr("0.0.0.0");
  addrLen[_pos] = sizeof(addr[_pos]);

  if (setsockopt(serverFd[_pos], SOL_SOCKET, SO_REUSEADDR,
    &opt, sizeof(opt)) < 0)
      throw std::logic_error(strerror(errno));

  if (bind(serverFd[_pos], (sockaddr *)&addr[_pos], addrLen[_pos]) <  0)
    throw std::logic_error(strerror(errno));

/*   int rc = ioctl(serverFd[_pos], FIONBIO, (char *)&opt);
  if (rc < 0)
  {
    perror("ioctl() failed");
    close(serverFd[_pos]);
    exit(-1);
  } */

  if (listen(serverFd[_pos], this->wConnections) < 0)
    throw std::logic_error("listen failed");
}

void  BaseServer::setSelect( void ) {
  
  FD_ZERO(&cSockets);
  for (int i = 0; i < nServers; i++)
    FD_SET(serverFd[i], &cSockets);
	while (true) {
		rSockets = cSockets;

		std::cout << "Arrived before-select" << std::endl;
		if (select(FD_SETSIZE, &rSockets, NULL, NULL, NULL) < 0) { // Waits until file descriptor has info
			perror("error: select");
			exit(EXIT_FAILURE);
		}

    for (int i = 0; i < nServers; i++) {
      if (FD_ISSET(serverFd[i], &rSockets) != 0)
        setClientSide(serverFd[i]);
    }
    std::cout << clientMsg << std::endl;
	}
}

void  BaseServer::setClientSide( int socket ) {
  if ((clientFd = accept(socket, (sockaddr *)&clientAddr, &addrClientLen)) < 0)
    throw std::logic_error("error: accept");
  timeout.tv_sec = 3; // 10 segundos
  timeout.tv_usec = 0;

  if (setsockopt(clientFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
      throw(std::runtime_error("error: setsockopt()"));
  if (recv(clientFd, clientMsg, sizeof(clientMsg) - 1, 0) <= 0) {
    close(socket);
    close(clientFd);
    throw std::logic_error("recv failed");
  }

  serverResponse = "HTTP/1.1 200  OK\r\n\r\n <html><head></head><body><h1 text-family=\"Roboto\" align=\"center\"> Hello, Inception42! </h1></body></html>";
  send(clientFd, serverResponse.data(), serverResponse.size(), 0);
  
  close(clientFd); // After server has replied, close connection
}

int   *BaseServer::getSockets(void) const { return (serverFd); }

int   BaseServer::getNServers( void ) const { return (nServers); }

bool   BaseServer::checkServer( int _nServer ) const {
  if (portAr[_nServer] <= 0 || server_nameAr[_nServer].empty())
    return false;
  return true;
}

void   BaseServer::setServerNumber( int _amount ) {
  this->nServers = _amount;
}

void BaseServer::setWConnections( int _amount ) {
  this->wConnections = _amount;
}

void BaseServer::setPortAr( int *_portAr ) {
  portAr = new int[nServers];
  for (int i = 0; i < nServers; i++)
    portAr[i] = _portAr[i];
}

void  BaseServer::setServerNameAr( const std::vector<string>& _sNameAr ) {
  this->server_nameAr = _sNameAr;
}

std::ostream &operator<<(std::ostream &os, const BaseServer &copy) {
  int *ret = copy.getSockets();
  for (int i = 0; i < copy.getNServers(); i++)
    os << "host: " << ret[i] << std::endl;
  return (os);
}
