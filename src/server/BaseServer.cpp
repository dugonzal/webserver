/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/03 19:21:02 by jaizpuru         ###   ########.fr       */
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
     throw logic_error("socket creation failed");

  assert((serverFd > 2) && (serverFd < 6553));
  addr.sin_family = AF_INET;
  cout << YEL << "Port : " << port << END;
  addr.sin_port = htons(port);
  cout << CYN << "Host : " << host << END;
  cout << "Server name : " << server_name << endl;
  cout << "socketFd: " << serverFd << endl << endl;
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
    cout << strerror(errno) << endl;
    cout << errno << endl;
    throw logic_error("error: socket bind().");
  }
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, \
    &opt, sizeof(opt)) < 0)
      throw logic_error("error: socket SO_REUSEADDR.");
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEPORT,
    &opt, sizeof(opt)) < 0)
      throw logic_error("error: socket SO_REUSEADDR.");
  if (bind(serverFd, (sockaddr *)&addr, addrLen) < 0) {
    cout << strerror(errno) << endl;
    throw logic_error("error: socket bind().");
  }
  if (listen(serverFd, 1024 / nServers) < 0)
    throw logic_error("listen failed");
}

void  BaseServer::setRequest( void ) {
  Request client(serverFd);
}

void  BaseServer::setLocations(const string &path, const Location &copy) {
  cout << path << endl;
  location.insert(make_pair(path, copy));
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

ostream &operator<<(ostream &os, const BaseServer &copy) {
  int ret = copy.getSocket();
  os << "host: " << ret << endl;
  return (os);
}
