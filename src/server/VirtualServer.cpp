/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/12 23:10:29 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/VirtualServer.hpp"

VirtualServer::VirtualServer(void) { }

VirtualServer::~VirtualServer(void) { }

VirtualServer::VirtualServer(const VirtualServer &copy): \
  server(copy.server) { }

VirtualServer &VirtualServer::operator=(const VirtualServer &copy) {
  if (this != &copy) {
    server = copy.server;
    nServers = copy.nServers;
    wConnections = copy.wConnections;
  }
  return (*this);
}

void  VirtualServer::setServers( size_t _amount ) {
  this->nServers = _amount;
}

void  VirtualServer::startServers( void ) {
  this->server.setServerNumber(nServers);
  this->server.setServerNameAr(nameServers);
  this->server.setPortAr(portsServers);
  this->server.setServer();
}

void  VirtualServer::setWorkerConnections( int _amount ) {
  std::cout << "Worker_Connections: " << _amount << std::endl;
  this->wConnections = _amount;
}

int   VirtualServer::setPort( int _nServer, int _port ) {
  //this->server.setPort(_port);
  this->portsServers[_nServer - 1] = _port;
  std::cout << "Port: " << _port << std::endl;
  return 0;
}

int   VirtualServer::setName( const std::string& _name ) {
  //this->server.setServerName(_name);
  this->nameServers.push_back(_name);
  std::cout << "Name: " << _name << std::endl << std::endl;
  return 0;
}
