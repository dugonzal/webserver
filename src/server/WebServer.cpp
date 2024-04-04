/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/04 21:51:49 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/WebServer.hpp"
#include <unistd.h>
#include <utility>

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
  servers.startServers();
}

void  WebServer::setLocation(const vector<string> &server, size_t i) {
  Location tmp;

  tmp.setPath(firstWord(lastWord(server[i])));
  while (++i < server.size()) {
    if (server[i].find("}") != string::npos)
      break;
    cout << server[i] << endl;
  }
  cout << tmp << endl;
  locations.insert(std::make_pair("hoña", tmp.clone()));
}

void  WebServer::printServer(const vector<string> &server, size_t n) {
  cout << "Server: " << n << endl;
  for (size_t i = 0; i < server.size(); i++) {
    if (server[i].find("listen", 0) != string::npos) {
      if (servers.setListenConfig((unsigned int)n, getHostFromLine(server[i]), \
        getNumberFromLine(server[i])))
          throw(runtime_error("error: setPort failed, bad values."));
    }
    else if (findStrInLog(server[i], "server_name") != "")
      servers.setServerName(findStrInLog(server[i], "server_name"));
   // else if (findStrInLog(*it, "error_page") != "")
    //  servers.setErrorPage(findStrInLog(*it, "error_page"));
    else if (findStrInLog(server[i], "client_max_body_size") != "")
      servers.setClientBodySize(findStrInLog(server[i], \
        "client_max_body_size"));
    else if (server[i].find("location") != string::npos) {
      setLocation(server, i);
    }
  }
  cout << endl << endl;
}
void  WebServer::setServerWebServer(void) {
  vector<string>  *tmp = parser.getDataServers();
  size_t          n = nServers;

  for (size_t i = 0; i < n; i++) {
    // hay que mejorar los servers vacios
    if (tmp[i].empty()) {
      --nServers;
      continue;
    }
    printServer(tmp[i], i);
  }
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
