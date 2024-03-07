/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/07 18:14:22 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/VirtualServer.hpp"

VirtualServer::VirtualServer(void) {
  std::cout << "VirtualServer object was created!" << std::endl;
}

VirtualServer::~VirtualServer(void) { }

VirtualServer::VirtualServer(const VirtualServer &copy): \
  vServers(copy.vServers) { }

VirtualServer &VirtualServer::operator=(const VirtualServer &copy) {
  if (this != &copy) {
    vServers = copy.vServers;
    nServers = copy.nServers;
    wConnections = copy.wConnections;
  }
  return (*this);
}

void VirtualServer::addServer(Server server) {
    vServers->push_back(server.clone());
}

void  VirtualServer::setServers( size_t _amount ) {
  this->nServers = _amount;
  vServers = new vector<Server *>[_amount];
  for (size_t i = 0; i < _amount; i++) {
    vServers->push_back(new Server());
  }
  std::cout << "Succesfully created " << _amount << " 'Server' objects !" << std::endl;
}

void  VirtualServer::setWorkerConnections( int _amount ) {
  std::cout << "Worker_Connections: " << _amount << std::endl;
  this->wConnections = _amount;
}

int   VirtualServer::setPort( int _nServer, int _port ) {
  if (portsServers == NULL) {
    if ( nServers <= 0 ) {
      return 1;
    }
    portsServers = new int[nServers];
  }
  if (_nServer <= 0 || _nServer > static_cast<int>(nServers))
    return 1;
  Server* ptr = (vServers->at(_nServer - 1)); // will work starting from one '1'
  ptr->setPort(_port);
  std::cout << "Port: " << _port << std::endl;
  return 0;
}

int   VirtualServer::setName( int _nServer, const std::string& _name ) {
  if (nameServers == NULL) {
    if ( nServers <= 0 ) {
      return 1;
    }
    nameServers = new int[nServers];
  }
  if (_nServer <= 0 || _nServer > static_cast<int>(nServers))
    return 1;
  Server* ptr = (vServers->at(_nServer - 1)); // will work starting from one '1'
  ptr->setServerName(_name);
  std::cout << "Name: " << _name << std::endl;
  return 0;
}
