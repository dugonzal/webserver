/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 10:40:38 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/ServerManager.hpp"

vector<pollfd>  fds;

ServerManager::ServerManager(void): nServers(0) { }

ServerManager::~ServerManager(void) {
  for (size_t it = 0; it < vServers.size(); it++)
    delete vServers[it];
}

ServerManager::ServerManager(const ServerManager &copy): \
  server(copy.server) { }

ServerManager &ServerManager::operator=(const ServerManager &copy) {
  if (this != &copy) {
    server = copy.server;
    nServers = copy.nServers;
  }
  return (*this);
}

bool  ServerManager::removeDuplicateServers(const string& host, int port) {
  for (size_t i = 0; i < vServers.size(); i++) {
    Location loc = vServers[i]->getLocation();
    if (loc.getHost() == host && loc.getPort() == port) {
      cout << RED << "host and port exist: " << host \
        << " " << port << END << endl;
      return (true);
    }
  }
  return (false);
}

void  ServerManager::startServers(void) {
  for (size_t n = 0; n < nServers; n++) {
    Location tmp = location[n].find("root")->second;
    if (removeDuplicateServers(tmp.getHost(), tmp.getPort()))
      continue;
    Server *ptr = new Server();
    ptr->setLocations(location[n]);
    ptr->setLocationRequest();
    ptr->setServerSide();
    vServers.push_back(ptr);
  }
  nServers = vServers.size();
  handlerPoll();
}

void ServerManager::initPoll(void) {
  for (size_t i = 0; i < nServers; i++) {
    struct pollfd pFd;
    bzero(&pFd, sizeof(pFd));
    pFd.fd = vServers[i]->getSocket();
    pFd.events = POLLIN;
    fds.push_back(pFd);
  }
}

void  ServerManager::addClient(void) {
  // handler sockets server | add client | handler
  for (size_t i = 0; i < nServers; i++) {
    if (fds[i].revents & POLLIN) {
      struct sockaddr client;
      struct pollfd   pFd;
      socklen_t clientLen = sizeof(client);
      bzero(&pFd, sizeof(pFd));
      int tmp = accept(fds[i].fd, \
        reinterpret_cast<sockaddr *>(&client), &clientLen);
      if (tmp < 0) {
        close(tmp);
        break;
      }
      if (fcntl(tmp, F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0) {
        close(tmp);
        break;
      }
      pFd.fd = tmp;
      pFd.events = POLLIN;
      fds.push_back(pFd);
      break;
    }
  }
}

bool  ServerManager::selectServerForClient(size_t fd) {
  char t[1024];

  int r = ::recv(fd, t, 1024, 0);
  if (r < 1) {
    close(fd);
    fds.erase(fds.begin() + fd);
    return (true);
  }
  t[r] = 0;
  string tmp(t);
  int pos = tmp.find("Host") + 6;
  int end = tmp.find('\n', pos);
  string addr = tmp.substr(pos, end - pos);

  int i = addr.find(":");
  int port = atoi(addr.substr(i + 1).data());
  string host = addr.substr(0, i);

  for (size_t i = 0; i < vServers.size(); i++) {
    if (vServers[i]->getHost() == host && vServers[i]->getPort() == port) {
      vServers[i]->handlerClient(fd, t);
      break;
    }
  }
  return (false);
}

void  ServerManager::handlerPoll(void) {
  initPoll();
  cout << CYN << "Inicio " << fds.size() << " Servidores" << END << endl;
  while (42) {
    if (poll(fds.data(), fds.size(), -1) < 0) {
      cerr << "error poll" << endl;
      Signals::setSignals(SIGQUIT);
    }
    addClient();
    for (size_t i = nServers; i < fds.size(); i++) {
      if (fds[i].revents & POLLIN)
        if (selectServerForClient(fds[i].fd))
          break;
    }
  }
}

void  ServerManager::setNServers(size_t _amount) { nServers = _amount; }

void  ServerManager::setLocations(map<string, Location> *_location) {
  location = _location;
}
