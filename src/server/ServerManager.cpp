/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/06 15:19:03 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/ServerManager.hpp"

ServerManager::ServerManager(void) {
  FD_ZERO(&cSockets);
  FD_ZERO(&rSockets);
  FD_ZERO(&wSockets);
  nServers = 0;
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

void  ServerManager::setLocations(map<string, Location> *tmp) {
  /*map<string, Location> **/locat = tmp;
  for (size_t i = 0; i < nServers; i++) {
    cout << locat[i].size() << endl;
  }
}

void  ServerManager::setNServers(size_t _amount) {
  nServers = _amount;
}

void  ServerManager::startServers(void) {
  for (size_t it = 0; it < nServers; it++) {
    Server ptr;

    ptr.setServerNumber(nServers);
    ptr.setPort(portsServers[it]);
    ptr.setHost(hostServers[it]);
    ptr.setServerName(serverName[it]);
    cout << endl << "------Server n.ª[" << it << "]----" << endl;
    ptr.setServerSide();
    addServer(ptr);
  }
//  setSelect();
}

void  ServerManager::setSelect(void) {
  for (size_t i = 0; i < nServers ; i++)
    FD_SET(vServers[i].getSocket(), &cSockets);
  while (true) {
    rSockets = cSockets;
		cout << RED << "!----SELECT ON POINT----!" << END << endl;
    int retSelect = select(FD_SETSIZE, &rSockets, NULL, NULL, &timeout);
    usleep(100000);
    if (retSelect < 0) { // Waits until file descriptor has info
			cout << "Select error" << endl;
      perror("error: select");
			exit(EXIT_FAILURE);
    }
    cout << "Available FDs : " << retSelect << endl << endl;
    for (int i = 0; i < FD_SETSIZE; i++) { // One or more descriptors may be available
      if (FD_ISSET(i, &rSockets)) { // check if 'i' number fd is available
        for (vector<Server>::iterator it = vServers.begin(); it != vServers.end(); it++) {
          if (i == it->getSocket()) {
            it->setRequest();
          }
        }
    }
      if (FD_ISSET(i, &wSockets))
        cout << i << " can be used to write!" << endl;
      else if (i == (int)nServers)
          i = 0;
    }
    // bzero(clientMsg, sizeof(clientMsg));
    }
}

void  ServerManager::addServer(Server _server) {
  vServers.push_back(_server.clone());
}

int   ServerManager::setServerName(const string& _name) {
  serverName.push_back(_name);
 // cout << "Name: " << _name << endl;
  return 0;
}

int   ServerManager::setListenConfig(int _nServer, const string &_host, int _port) {
  portsServers.push_back(_port);
  hostServers.push_back(_host);
  (void)_nServer;
//  cout << "Port: " << _port << " (" << _nServer << ")." << endl;
//  cout << "Host: " << _host << " (" << _nServer << ")." << endl;
  return 0;
}

/*
int ServerManager::setErrorPage( const std::string& _errorPages ) {
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
    ss.str(string()); // clear std::stringstream
  }
  return 0;
}*/

int ServerManager::setClientBodySize(const string& _clientBodySize) {
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
