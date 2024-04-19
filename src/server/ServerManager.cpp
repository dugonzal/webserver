/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/19 18:15:01 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/ServerManager.hpp"


ServerManager::ServerManager(void): nServers(0) {
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
  for (vector<Server>::const_iterator it = vServers.begin(); it < vServers.end(); it++) {
    struct pollfd tmp;
    tmp.fd = it->getSocket();
    tmp.events = POLLIN;
    fds.push_back(tmp);
  }

  while (42) {
      cout << "klk" << endl;
      sleep(10);
  }
  while (true) {
    if (poll(fds.data(), fds.size(), timeout.tv_sec ) < 0)
      throw(runtime_error("eerrr poll"));

    cout << "xd" << endl;
    for (size_t i = 0; i < fds.size(); i++) {
      if (fds[i].revents & POLLIN) {
          cout << "entra un server" << endl;
          cout << "entra un cliente" << endl;
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
