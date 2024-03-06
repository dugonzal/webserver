/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/06 23:34:50 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/VirtualServer.hpp"

VirtualServer::VirtualServer(void) { }

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
  for (size_t i = 0; i < _amount; ++i) {
    vServers->push_back(new Server());
  }
  std::cout << "Succesfully created " << _amount << " 'Server' objects !" << std::endl;
}

void  VirtualServer::setWorkerConnections( int _amount ) {
  this->wConnections = _amount;
}
