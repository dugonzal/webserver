/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/19 20:06:14 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/ServerManager.hpp"

vector<pollfd>  fds;

ServerManager::ServerManager(void): nServers(0) { }

ServerManager::~ServerManager(void) { }

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
  cout << "# servers: " << nServers << endl;
  for (size_t it = 0; it < nServers; it++) {
    Server ptr;
    cout << endl << "------Server n.ª[" << it << "]----" << endl;
    ptr.setLocations(location[it]);
    ptr.setServerSide();
    addServer(ptr);
  }
  setSelect();
}


void  ServerManager::setSelect(void) {
  for (vector<Server>::const_iterator it = vServers.begin(); \
    it < vServers.end(); it++) {
      struct pollfd tmp;
      tmp.fd = it->getSocket();
      tmp.events = POLLIN;
      fds.push_back(tmp);
  }
  cout << "server" << fds.size() << endl;
  char *recvClient[1024] = {0};
  const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
  while (true) {
    if (poll(fds.data(), fds.size(), -1) < 0)
      throw(runtime_error("eerrr poll"));
    for (size_t i = 0; i < fds.size(); i++) {
      cout << "n:   " << i << endl;
      if (fds[i].revents & POLLIN)  {
        cout << "n: match " << i << endl;
        if (i < nServers) {
          cout << "socket server es un nuevo cliente" << endl;
          struct pollfd fd;
          struct sockaddr client;
          socklen_t clientLen = sizeof(client);

          int tmp = accept(fds[i].fd, \
            reinterpret_cast<sockaddr *>(&client), &clientLen);
          if (tmp < 0) {
            std::cerr << "error client " << endl;
            Signals::setSignals(SIGQUIT);
            throw(runtime_error("error al aceptar un cliente"));
          }
          fd.fd = tmp;
          fd.events = POLLIN;
          if (::recv(tmp, recvClient, sizeof(recvClient), 0) < 0) {
            std::cerr << "error al recibir" << endl;
            Signals::setSignals(SIGQUIT);
            throw(runtime_error("error al aceptar un cliente"));
          }
          send (tmp, response, strlen(response), 0);
          fds.push_back(fd);
        } else {
          cout << "es un cliente" << endl;
          int pos = ::recv(fds[i].fd, recvClient, sizeof(recvClient), 0);
          if (pos < 0) {
            std::cerr << "error al recibir" << endl;
            Signals::setSignals(SIGQUIT);
          }
          if (!pos) {
            close(fds[i].fd);
            fds.erase(fds.begin() + i);
          }
          send (fds[i].fd, response, strlen(response), 0);
          cout << recvClient << endl;
        }
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

void  ServerManager::addServer(Server _server) {
  vServers.push_back(_server.clone());
}
