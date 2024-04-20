/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/20 13:58:17 by Dugonzal         ###   ########.fr       */
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

void  ServerManager::startServers(void) {
  vServers.reserve(nServers);
  for (size_t n = 0; n < nServers; n++) {
    Server *ptr = new Server();
    ptr->setLocations(location[n]);
    ptr->setServerSide();
    vServers.push_back(ptr);
  }
  handlerPoll();
}

void ServerManager::initPoll(void) {
  fds.reserve(nServers);
  for (size_t i = 0; i < vServers.size(); i++) {
    struct pollfd tmp;
    tmp.fd = vServers[i]->getSocket();
    tmp.events = POLLIN | POLLERR | POLLHUP;
    tmp.revents = 0;
    fds.push_back(tmp);
  }
}

void  ServerManager::handlerPoll(void) {
  const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";

  initPoll();
  while (true) {
    if (poll(fds.data(), fds.size(), -1) < 0) {
      cerr << "error poll" << endl;
      Signals::setSignals(SIGQUIT);
    }
    // handler sockets server | add client | handler
    for (size_t i = 0; i < nServers; i++) {
      if (fds[i].revents & POLLIN)  {
          struct pollfd fd;
          struct sockaddr client;
          socklen_t clientLen = sizeof(client);

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
          fd.fd = tmp;
          fd.events = POLLIN | POLLERR | POLLHUP;
          fd.revents = 0;
          fds.push_back(fd);
          break;
      }
    }
    // event clients
    for (size_t i = nServers; i < fds.size(); i++) {
      if (fds[i].revents & POLLIN) {
        // req
        char t[1024];
        int pos = ::recv(fds[i].fd, t, 1024, 0);
          if (pos < 1) {
            close(fds[i].fd);
            fds.erase(fds.begin() + i);
            break;
          }
          t[pos] = 0;
          cout << t << endl;
          // res
          if (send(fds[i].fd, response, strlen(response), 0) < 0) {
          std::cerr << "error al enviar" << endl;
          }
          break;
      }
    }
  }
}

void  ServerManager::setNServers(size_t _amount) {
  nServers = _amount;
}

void  ServerManager::setLocations(map<string, Location> *_location) {
  location = _location;
}
