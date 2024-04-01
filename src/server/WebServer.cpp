/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/01 15:41:30 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/WebServer.hpp"
#include <vector>

WebServer::WebServer(void) { }

WebServer::~WebServer(void) { }

WebServer::WebServer(const string &filename): parser(filename) {
  nServers = parser.getNservers();
}

WebServer::WebServer(const WebServer &copy): \
  servers(copy.servers), parser(copy.parser), signals(copy.signals) { }

WebServer &WebServer::operator=(const WebServer &copy) {
  if (this != &copy) {
    servers = copy.servers;
    parser = copy.parser;
    signals = copy.signals;
  }
  return (*this);
}

void  WebServer::setServer(void) {
  setServerWebServer();
  servers.setNServers(nServers);
//  servers.startServers();
}

void  printServer(const vector<string> &server) {
  for (vector<string>::const_iterator it = server.begin(); it != server.end(); it++)
    cout << *it << endl;
}
void  WebServer::setServerWebServer(void) {
  vector<string>  *tmp = parser.getDataServers();
  unsigned int    n = nServers;

  cout << endl << n << endl;
  for (unsigned int i = 0; i < n; i++) {
    if (tmp[i].empty()) {
      --nServers;
      continue;
    }
    cout << endl << "nServer: (" << i << ")" << endl;
    printServer(tmp[i]);
    cout << endl;
  }
  cout << nServers << endl;
}
/*
void  WebServer::setServerWebServer(void) {
  vector<string> ptrData = parser.getData();
  int sCount = 0;

  for (vector<string>::const_iterator it = ptrData.begin(); \
    it != ptrData.end(); it++) {
    if (it->find("listen", 0) != string::npos) {
      if (servers.setPort(sCount, getHostFromLine(*it), \
        getNumberFromLine(*it)))
          throw(runtime_error("error: setPort failed, bad values."));
    }
    else if (findStrInLog(*it, "server_name") != "")
      servers.setName(findStrInLog(*it, "server_name"));
    else if (findStrInLog(*it, "error_page") != "")
      servers.setErrorPage(findStrInLog(*it, "error_page"));
    else if (findStrInLog(*it, "client_max_body_size") != "")
      servers.setClientBodySize(findStrInLog(*it, \
        "client_max_body_size"));
    else if (!it->compare("};")) {
      cout << endl;
      sCount++;
    }
    else if (it->find("location") != string::npos) {
      cout << sCount << endl;
      cout << *it << endl;
    }
  }
  cout << endl;
}*/
