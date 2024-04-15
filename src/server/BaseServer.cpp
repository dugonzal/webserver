/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/15 17:51:51 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"

BaseServer::BaseServer(void): opt(1) {
  addrLen = sizeof(addr);
  ::bzero(&addr, addrLen);
}

BaseServer::BaseServer(const BaseServer &copy): \
  serverFd(copy.serverFd), opt(copy.opt), addrLen(copy.addrLen) { }

BaseServer &BaseServer::operator=(const BaseServer &copy) {
  if (this != &copy) {
    addr = copy.addr;
    addrLen = copy.addrLen;
    serverFd = copy.serverFd;
    buffer = copy.buffer;
    location = copy.location;
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
/*   struct flock fvar;
  fvar.l_type=F_WRLCK;
  fvar.l_whence=SEEK_END;
  fvar.l_start=-100;
  fvar.l_len=100;

  if (fcntl(serverFd, O_NONBLOCK, &fvar) < 0 ) { */

  if (fcntl(serverFd, F_SETFD, O_NONBLOCK) < 0) {
    close(serverFd);
    throw logic_error("error: socket bind().");
  }
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
      throw logic_error("error: socket SO_REUSEADDR.");
  if (bind(serverFd, reinterpret_cast<sockaddr *>(&addr), addrLen) < 0)
    throw logic_error("error: socket bind().");
  if (listen(serverFd, nServers / 1024) < 0)
    throw logic_error("listen failed");
}

void  BaseServer::setRequest(void) {
  Request client(serverFd);
}

void  BaseServer::setLocations(const map<string, Location> &copy) {
  location = copy;

  LocationRoot = location.find("root")->second;
  host = LocationRoot.getHost();
  port = LocationRoot.getPort();
  server_name = LocationRoot.getServerName();
}

int BaseServer::getSocket(void) const { return (serverFd); }

size_t  BaseServer::getNServers(void) const { return (nServers); }

ostream &operator<<(ostream &os, const BaseServer &copy) {
  int ret = copy.getSocket();
  os << "host: " << ret << endl;
  return (os);
}
