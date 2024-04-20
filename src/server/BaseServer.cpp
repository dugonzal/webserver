/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/20 16:39:15 by Dugonzal         ###   ########.fr       */
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
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(host.data());
  if (fcntl(serverFd, F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0) {
    close(serverFd);
    throw logic_error("error: socket bind().");
  }
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
      throw logic_error("error: socket SO_REUSEADDR.");
  if (bind(serverFd, reinterpret_cast<sockaddr *>(&addr), addrLen) < 0)
    throw logic_error("error: socket bind().");
  if (listen(serverFd, 1024) < 0)
    throw logic_error("listen failed");
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

Location  BaseServer::getLocation(void) const { return (LocationRoot); }

ostream &operator<<(ostream &os, const BaseServer &copy) {
  int ret = copy.getSocket();
  os << "host: " << ret << endl;
  return (os);
}
