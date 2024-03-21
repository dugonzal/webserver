/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/20 16:16:48 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/VirtualServer.hpp"

VirtualServer::VirtualServer(void) { }

VirtualServer::~VirtualServer(void) {
  /// delete temporal vServers
  for (unsigned int i = 0; i < vServers.size(); i++) {
    delete vServers[i];
  }
  vServers.clear();
}

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
  for (size_t it = 0; it < nServers; it++) {
    Server *ptr = new Server;
    ptr->setServerNumber(nServers);
    ptr->setPort(portsServers[it]);
    ptr->setHost(hostServers[it]);
    ptr->setServerName(nameServers[it]);
    ptr->setServerSide();
    vServers.push_back(ptr);
  }
  setSelect();
}

void  VirtualServer::setSelect( void ) {
  timeout.tv_sec = 900; // timeout for select()
  timeout.tv_usec = 0;

  FD_ZERO(&cSockets);
  for (size_t i = 0; i < nServers; i++) {
    Server* ptr1 = vServers[i];
    FD_SET(ptr1->getSocket(), &cSockets);
  }
	while (true) {
		rSockets = cSockets;

		std::cout << "Arrived before-select" << std::endl;
    int retSelect = select(FD_SETSIZE, &rSockets, NULL, NULL, &timeout);
		if (retSelect < 0) { // Waits until file descriptor has info
			perror("error: select");
			exit(EXIT_FAILURE);
    }
    else if (retSelect == 0) {
      perror("select() timeout\n");
      exit(EXIT_FAILURE);
    }
    std::cout << "Available FDs : " << retSelect << std::endl << std::endl;

    usleep(100000);
    for (int i = 0; i < FD_SETSIZE; i++) { // One or more descriptors may be available
      if (FD_ISSET(i, &rSockets)) { // check if 'i' number fd is available
        for (size_t j = 0; j < nServers; j++) {
          Server* ptr2 = vServers[j];
          if (ptr2->getSocket() == i) { // check if it forms part of our descriptors
            ptr2->setRequest();
          }
        }
      }
      if (FD_ISSET(i, &wSockets))
        std::cout << i << " can be used to write!" << std::endl;
    }
    // bzero(clientMsg, sizeof(clientMsg));
	}
}

int   VirtualServer::setName( const std::string& _name ) {
  //this->server.setServerName(_name);
  this->nameServers.push_back(_name);
  //std::cout << "Name: " << _name << std::endl;
  return 0;
}

int   VirtualServer::setPort( __unused int _nServer, const std::string& _host, int _port ) {
  portsServers.push_back(_port);
  hostServers.push_back(_host);
  //std::cout << "Port: " << _port << " (" << _nServer << ")." << std::endl;
  //std::cout << "Host: " << _host << " (" << _nServer << ")." << std::endl;
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
  //std::cout << "Error_page: " << std::endl;

  for (size_t i = 0; i < _errorPages.size() && isdigit(errorPages[i]); i++) { // get numbers
    for (size_t j = 0; j < 3; j++) {
      ss << errorPages[i];
      i++;
    }
    i--;
    ret = atoi(ss.str().c_str());
    std::pair<int, std::string> content(ret, error_page);
    //std::cout << "[ " << ret << " , " << error_page << " ]" << std::endl;
    this->errorPage.insert(content);
    ss.str(std::string()); // clear std::stringstream
  }
  return 0;
}

int   VirtualServer::setClientBodySize( const std::string& _clientBodySize ) {
  std::stringstream num;
  std::stringstream size;
  __unused int ret;

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
  //std::cout << "Body Size : " << ret << std::endl;
  return 0;
}
