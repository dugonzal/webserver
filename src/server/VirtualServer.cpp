/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/15 17:29:33 by jaizpuru         ###   ########.fr       */
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
  }
  return (*this);
}

void  VirtualServer::setServers( size_t _amount ) {
  this->nServers = _amount;
}

void  VirtualServer::startServers( void ) {
  this->server.setServerNumber(nServers);
  this->server.setServerName(nameServers);
  this->server.setPort(portsServers);
  this->server.setHost(hostServers);
  this->server.setServer();
}

int   VirtualServer::setName( const std::string& _name ) {
  //this->server.setServerName(_name);
  this->nameServers.push_back(_name);
  std::cout << "Name: " << _name << std::endl;
  return 0;
}

int   VirtualServer::setPort( int _nServer, const std::string& _host, int _port ) {
  portsServers.push_back(_port);
  hostServers.push_back(_host);
  std::cout << "Port: " << _port << " (" << _nServer << ")." << std::endl;
  std::cout << "Host: " << _host << " (" << _nServer << ")." << std::endl;
  return 0;
}

int   VirtualServer::setErrorPage( const std::string& _errorPages ) {
  const char *errorPages = _errorPages.c_str();
  std::stringstream ss;
  int ret;
  size_t  strSpace;

  for (size_t i = _errorPages.size() - 1; errorPages[i] && !isdigit(errorPages[i]); i--) { // get size of path
    strSpace = i;
  }
  for (size_t i = strSpace; errorPages[i]; i++) { // get path to error_page
    ss << errorPages[i];
  }

  std::string error_page = ss.str();
  ss.str(std::string()); // clear std::stringstream
  std::cout << "Error_page: " << std::endl;

  for (size_t i = 0; i < _errorPages.size() && isdigit(errorPages[i]); i++) { // get numbers
    for (size_t j = 0; j < 3; j++) {
      ss << errorPages[i];
      i++;
    }
    i--;
    ret = atoi(ss.str().c_str());
    std::pair<int, std::string> content(ret, error_page);
    std::cout << "[ " << ret << " , " << error_page << " ]" << std::endl;
    this->errorPage.insert(content);
    ss.str(std::string()); // clear std::stringstream

  }
  return 0;
}

int   VirtualServer::setClientBodySize( const std::string& _clientBodySize ) {
  std::stringstream num;
  std::stringstream size;
  int ret;

  for (size_t i = 0; i < _clientBodySize.size(); i++) {
    if (isdigit(_clientBodySize.c_str()[i]))
      num << _clientBodySize.c_str()[i];
    else
      size << _clientBodySize.c_str()[i];
  }
  ret = atoi(num.str().c_str());
  if (!size.str().compare("m"))
    ret *= 1000000;
  else if (!size.str().compare("k"))
    ret *= 1000;
  std::cout << "Body Size : " << ret << std::endl;
  return 0;
}
