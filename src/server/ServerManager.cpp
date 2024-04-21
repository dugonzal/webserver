/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 19:42:50 by Dugonzal         ###   ########.fr       */
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
      logger.Log("host and port exist skiped [%s] [%d]", host.data(), port);
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
    logger.Log("socket listen created, [%d]", pFd.fd);
    pFd.events = POLLIN;
    fds.push_back(pFd);
  }
}

void  ServerManager::addClient(void) {
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
      logger.Log("new cliente [%d] ", tmp);
      fds.push_back(pFd);
      break;
    }
  }
}

bool  ServerManager::selectServerForClient(size_t fd) {
  char header[1025];

  int r = ::recv(fd, header, 1024, 0);
  if (r < 0) {
    close(fd);
    fds.erase(fds.begin() + fd);
    logger.Log("error recv client: [%d]", fd);
    return (true);
  } else if (!r) {
    close(fd);
    fds.erase(fds.begin() + fd);
    logger.Log("close client: [%d]", fd);
    return (true);
  }
  header[r] = 0;
  string tmp(header);
  int pos = tmp.find("Host") + 6;
  int end = tmp.find('\n', pos);
  string addr = tmp.substr(pos, end - pos);

  int i = addr.find(":");
  int port = atoi(addr.substr(i + 1).data());
  string host = addr.substr(0, i);

  for (size_t i = 0; i < vServers.size(); i++) {
    if (vServers[i]->getHost() == host && vServers[i]->getPort() == port) {
      vServers[i]->handlerClient(fd, header);
      break;
    }
  }
  return (false);
}

void  ServerManager::handlerPoll(void) {
  initPoll();
  logger.Log("|--Inicio de servidor--|");
  while (42) {
    if (poll(fds.data(), fds.size(), -1) < 0) {
      logger.Log("error poll");
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
