/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/19 12:14:52 by jaizpuru         ###   ########.fr       */
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
  ClientSide client(serverFd);
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
