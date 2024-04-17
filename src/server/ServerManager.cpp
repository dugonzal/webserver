/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/15 21:20:10 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/ServerManager.hpp"

ServerManager::ServerManager(void): nServers(0) {
  FD_ZERO(&cSockets);
  FD_ZERO(&rSockets);
  FD_ZERO(&wSockets);
  timeout.tv_sec = 90;
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
  setSelect();
}

void  ServerManager::setSelect(void) {
  int retSelect = 0;

  for (size_t i = 0; i < nServers ; i++)
    FD_SET(vServers[i].getSocket(), &cSockets);
  while (true) {
    rSockets = cSockets;
    cout << RED << "!----SELECT ON POINT----!" << END << endl;
    if ((retSelect = select(FD_SETSIZE, &rSockets, NULL, NULL, &timeout)) < 0) {
      throw(runtime_error("error select"));
    }
    for (int i = 0; i < FD_SETSIZE; i++) {
      if (FD_ISSET(i, &rSockets)) {
        cout << i << endl;
        for (vector<Server>::iterator it = vServers.begin(); \
          it != vServers.end(); it++) {
            if (i == it->getSocket()) {
              int newSocket;
              sockaddr_in addr;
              socklen_t addr_size = sizeof(addr);
              newSocket = accept(it->getSocket(), (struct sockaddr *)&addr, &addr_size);
              FD_SET(newSocket, &cSockets);
              cout << "New connection on socket: " << newSocket << endl;
              char buffer[1024] = {0};
              if (::recv(newSocket, buffer, 1024, 0) < 0) {
                cout << "cierra socket" << endl;
                close (newSocket);
                FD_CLR(newSocket, &cSockets); // remove from master set
              }
              if (send(newSocket, "Hello, world!", 13, 0) < 0) {
                close (newSocket);
                FD_CLR(newSocket, &cSockets); // remove from master set
              }
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
