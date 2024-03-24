/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/24 17:13:00 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"
#include <utility>

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
    options = copy.options;
    locations = copy.locations;
  }
  return (*this);
}

BaseServer::~BaseServer(void) { }

void  BaseServer::setServerSide(void) {
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
/*   struct flock fvar;
  fvar.l_type=F_WRLCK;
  fvar.l_whence=SEEK_END;
  fvar.l_start=-100;
  fvar.l_len=100;

  if (fcntl(serverFd, O_NONBLOCK, &fvar) < 0 ) { */

  if (fcntl(serverFd, F_SETFD, O_NONBLOCK) < 0) {
    close(serverFd);
    std::cout << strerror(errno) << std::endl;
    std::cout << errno << std::endl;
    throw std::logic_error("error: socket bind().");
  }
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

void  BaseServer::setLocations(const string &path, const Location &copy) {
  cout << path << endl;
  sleep(3);
  location.insert(std::make_pair(path, copy));
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

void BaseServer::setHost(const string& _host) {
  host = _host;
}

void  BaseServer::setServerName(const string& _name ) {
  this->server_name = _name;
}

std::ostream &operator<<(std::ostream &os, const BaseServer &copy) {
  int ret = copy.getSocket();
  os << "host: " << ret << std::endl;
  return (os);
}
