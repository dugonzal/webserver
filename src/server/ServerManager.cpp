/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal Dugonzal@student.42urduliz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/06/18 17:25:43 by Dugonzal         ###   ########.fr       */
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
  if (this not_eq &copy) {
    server = copy.server;
    nServers = copy.nServers;
  }
  return (*this);
}

bool  ServerManager::removeDuplicateServers(const string& host, int port) {
  for (size_t i = 0; i < vServers.size(); i++) {
    Location loc = vServers[i]->getLocation();
    if (loc.getHost() == host and loc.getPort() == port) {
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
    ::bzero(&pFd, sizeof(pFd));
    pFd.fd = vServers[i]->getSocket();
    logger.Log("socket listen created, [%d]", pFd.fd);
    pFd.events = POLLIN;
    fds.push_back(pFd);
  }
}

void  ServerManager::addClient(void) {
  for (size_t i = 0; i < nServers; i++) {
    if (fds[i].revents & POLLIN) { /* Check if file descriptor can be read */
      struct sockaddr client;
      struct pollfd   pFd;
      socklen_t clientLen = sizeof(client);
      ::bzero(&pFd, sizeof(pFd));
      int tmp = accept(fds[i].fd, \
        reinterpret_cast<sockaddr *>(&client), &clientLen);
      if (tmp < 0) {
        ::close(tmp);
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

bool  ServerManager::selectServerForClient(size_t fd, size_t i) {
  char header[1025];


  int r = ::recv(fd, header, 1024, 0);
  if (r < 0) {
    ::close(fd);
    fds.erase(fds.begin() + i);
    logger.Log("error recv client: [%d]", fd);
    return (true);
  } else if (!r) {
    ::close(fd);
    fds.erase(fds.begin() + i);
    logger.Log("close client: [%d]", fd);
    return (true);
  }
  header[r] = 0;
  string tmp(header);
  size_t pos = tmp.find("Host");
  if (pos == string::npos) {
    ::close(fd);
    fds.erase(fds.begin() + i);
    logger.Log("error: bad header");
    return (true);
  }
  pos += 6;
  size_t end = tmp.find('\n', pos);
  string addr = tmp.substr(pos, end - pos);

  size_t idx = addr.find(":");
  int port = atoi(addr.substr(idx + 1).data());
  string host = addr.substr(0, idx);
  if (!host.compare("localhost"))
    host = "127.0.0.1";

  for (size_t i = 0; i < vServers.size(); i++) {
    if (vServers[i]->getHost() == host and vServers[i]->getPort() == port) {
      vServers[i]->handlerClient(fd, header);
      break;
    }
  }
  return (false);
}
 /**
  * @brief Tests to check error cases with non-blocking sockets
  * 
  *  If we try to use accept() with sockets set to non-blocking &
  *   no connections are available, we will get an error due to 
  *   this behaviour.
  * 
  */
void  ServerManager::errBlocking( void ) {
  int tmp = accept(fds[0].fd, NULL, NULL);
    std::cout << "Returning Value of accept() : " << tmp << std::endl;
    if (errno == EAGAIN) // Check library to see error code
      std::cout << "Errno value is : " << errno << std::endl;
}

void  ServerManager::handlerPoll(void) {
  int max = 1024;

  initPoll();
  logger.Log("|--Inicio de servidor--|");
  while (42) {
    // errBlocking();
    max = poll(fds.data(), fds.size(), -1);
    if (max < 0) {
      logger.Log("error poll");
    }
    addClient();
    for (size_t i = nServers; i < fds.size(); i++) {
      if (fds[i].revents & POLLIN)
        if (selectServerForClient(fds[i].fd, i))
          break;
    }
  }
}

void  ServerManager::setNServers(size_t _amount) { nServers = _amount; }

void  ServerManager::setLocations(map<string, Location> *_location) {
  location = _location;
}
