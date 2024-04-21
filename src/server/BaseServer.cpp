/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 18:47:50 by Dugonzal         ###   ########.fr       */
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
  if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    logger.Log("socket creation failed");
    throw logic_error("");
  }

  assert((serverFd > 2) && (serverFd < 6553));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(host.data());

  if (fcntl(serverFd, F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0) {
    close(serverFd);
    logger.Log("error: socket bind().");
    throw logic_error("");
  }
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    logger.Log("error: socket SO_REUSEADDR.");
    throw logic_error("");
  }
  if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
    logger.Log("error: socket SO_REUSEPORT.");
    throw logic_error("");
  }
  if (bind(serverFd, reinterpret_cast<sockaddr *>(&addr), addrLen) < 0) {
    logger.Log("error: socket bind().");
    throw logic_error("");
  }
  if (listen(serverFd, 1024) < 0) {
    logger.Log("listen failed");
    throw logic_error("");
  }
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

const string  BaseServer::getHost(void) const { return(host);}

int BaseServer::getPort(void) const { return(port); }

ostream &operator<<(ostream &os, const BaseServer &copy) {
  os << "host: " << copy.host << endl;
  return (os);
}
