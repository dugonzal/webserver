/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/14 11:52:42 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/ServerManager.hpp"

ServerManager::ServerManager(void): nServers(0) {
  FD_ZERO(&cSockets);
  FD_ZERO(&rSockets);
  FD_ZERO(&wSockets);
  timeout.tv_sec = 900;
  timeout.tv_usec = 0;
}

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
  for (size_t it = 0; it < nServers; it++) {
    Server ptr;
    cout << endl << "------Server n.ª[" << it << "]----" << endl;
    ptr.setLocations(location[it]);
    ptr.setServerSide();
    addServer(ptr);
  }
  //setSelect();
}

void  ServerManager::setSelect(void) {
  int retSelect = 0;

  for (size_t i = 0; i < nServers ; i++)
    FD_SET(vServers[i].getSocket(), &cSockets);
  while (true) {
    rSockets = cSockets;
    cout << RED << "!----SELECT ON POINT----!" << END << endl;
    if (!(retSelect = select(FD_SETSIZE, &rSockets, NULL, NULL, &timeout))) {
      throw(runtime_error("error select"));
    }
    for (int i = 0; i < FD_SETSIZE; i++) {
      if (FD_ISSET(i, &rSockets)) {
        for (vector<Server>::iterator it = vServers.begin(); \
          it != vServers.end(); it++) {
            if (i == it->getSocket()) {
              it->setRequest();
            }
        }
      }
      if (FD_ISSET(i, &wSockets))
        cout << i << " can be used to write!" << endl;
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
