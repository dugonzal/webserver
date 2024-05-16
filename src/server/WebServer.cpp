/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/16 19:06:15 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/WebServer.hpp"

WebServer::WebServer(void) { }

WebServer::~WebServer(void) { delete [] locations; }

WebServer::WebServer(const string &filename): parser(filename), signals() {
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
  system("clear");
  handlerSetServerWebServer();
  servers.setNServers(nServers);
  servers.setLocations(locations);
  servers.startServers();
}

void  WebServer::insertLocation(Location *tmp, const string &line) {
  if (!firstWord(line).compare("root"))
    tmp->setRoot(lastWord(line));
  else if (!firstWord(line).compare("cgi_path"))
    tmp->setCgiPath(lastWord(line));
  else if (!firstWord(line).compare("autoindex"))
    tmp->setAutoIndex(lastWord(line));
  else if (!firstWord(line).compare("allow_methods"))
    tmp->setMethods(lastWord(line));
  else if (!firstWord(line).compare("error_page"))
    tmp->setErrorPages(lastWord(line));
  else if (!firstWord(line).compare("return"))
    tmp->setReturn(lastWord(line));
  else if (!firstWord(line).compare("client_max_body_size"))
    tmp->setClientBodySize(lastWord(line));
  else if (!firstWord(line).compare("index"))
    tmp->setIndex(lastWord(line));
  else if (!firstWord(line).compare("listen"))
    tmp->setListen(lastWord(line));
  else if (!firstWord(line).compare("server_name"))
    tmp->setServerName(lastWord(line));
  else if (!firstWord(line).compare("alias"))
    tmp->setAlias(lastWord(line));
}

void  WebServer::setLocations(const vector<string> &line, size_t n) {
  Location tmp;

  for (size_t i = 0; i < line.size(); i++) {
    if (line[i].find("location") != string::npos \
      && line[i].find("{") != string::npos) {
        while (++i < line.size())
          if (!line[i].compare("}"))
            break;
    }
    insertLocation(&tmp, line[i]);
  }

  tmp.setPath("root");
  locations[n].insert(make_pair(tmp.getPath(), tmp.clone()));
  tmp.clear();
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i].find("location") != string::npos && line[i].find("{") != string::npos) {
      if (locations[n].find(firstWord(lastWord(line[i]))) != locations[n].end())
        logger.LogThrow("error: location already exists. ", line[i].data());
      tmp.setPath(firstWord(lastWord(line[i])));
      while (++i < line.size()) {
        if (!line[i].compare("}")) {
          locations[n].insert(make_pair(tmp.getPath(), tmp.clone()));
          tmp.clear();
          break;
        }
        insertLocation(&tmp, line[i]);
      }
    }
  }
}

void  WebServer::handlerSetServerWebServer(void) {
  const vector<string> *tmp = parser.getDataServers();
  locations = new map<string, Location>[nServers];

  for (size_t i = 0; i < nServers; i++)
    setLocations(tmp[i], i);
}
