/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/19 21:44:17 by Dugonzal         ###   ########.fr       */
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
  cout << "# servers: " << nServers << endl;
  for (size_t it = 0; it < nServers; it++) {
    Server *ptr = new Server();
    cout << endl << "------Server n.ª[" << it << "]----" << endl;
    ptr->setLocations(location[it]);
    ptr->setServerSide();
    vServers.push_back(ptr);
  }
  for (size_t it = 0; it < vServers.size(); it++) {
    cout << vServers[it]->getLocation()  << endl;
  }
//  setSelect();
}

/*
void  ServerManager::setSelect(void) {
  for (vector<Server*>::const_iterator it = vServers->begin(); \
    it < vServers.end(); it++) {
      struct pollfd tmp;
      tmp.fd = it->getSocket();
      cout << it->getLocation().getHost() << "  " << it->getLocation().getPort() << endl;
      tmp.events = POLLIN;
      fds.push_back(tmp);
  }
  const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
  while (true) {
    if (poll(fds.data(), fds.size(), -1) < 0)
      throw(runtime_error("eerrr poll"));
    cout << "n-----------------------------------------n" << endl;
    for (size_t i = 0; i < nServers; i++) {
      if (fds[i].revents & POLLIN)  {
          cout << "es un server que quiere agregar un cliente" << endl;
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
          fds.push_back(fd);
          break;
      }
    }
    for (size_t i = nServers; i < fds.size(); i++) {
      cout << "n:   " << i << endl;
      if (fds[i].revents & POLLIN)  {
        cout << "n: match " << i << endl;
          cout << "es un cliente" << endl;
        char t[1024];
        int pos = ::recv(fds[i].fd, t, 1024, 0);
          if (pos < 0) {
            std::cerr << "error al recibir" << endl;
            Signals::setSignals(SIGQUIT);
          }
          if (!pos) {
            close(fds[i].fd);
            fds.erase(fds.begin() + i);
          }
          t[pos] = 0;
          cout << t << endl;
          if (send (fds[i].fd, response, strlen(response), 0) < 0) {
            throw(runtime_error("errro send"));
          }
          break;
      }
    }
  }
}
*/
void  ServerManager::setNServers(size_t _amount) {
  nServers = _amount;
}

void  ServerManager::setLocations(map<string, Location> *_location) {
  location = _location;
}
