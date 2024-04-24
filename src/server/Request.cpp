/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:48:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/24 22:20:11 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Request.hpp"

Request::Request(void) { }

Request::~Request(void) { }

Request::Request(const Request &copy) {
  if (this != &copy) {
    header = copy.header;
  }
}

Request &Request::operator=(const Request &copy) {
  if (this != &copy) {
    header = copy.header;
  }
  return (*this);
}

void Request::setHeader(const char *_header) {
  header = _header;
}

void  Request::setLocation(const map<string, Location> &tmp) {
    locations = tmp;
}

bool  Request::setMethod(const string &_method) {
  vector<string> tmp = locationRoot.getmethods();
  for (size_t i = 0; i < tmp.size(); i++) {
    if (!tmp[i].compare(_method)) {
      method = _method;
      return (false);
    }
  }

  if (_method.compare("GET") && _method.compare("DELETE") \
    && _method.compare("POST")) {
      return (true);
  }
  return (true);
}

void  Request::setLocation(void) {
  map<string, Location>::iterator it = locations.find(route);
  if (it != locations.end()) {
    locationRoot = it->second;
    isCgi =  it->second.getIsCgi();
  } else {
    locationRoot = locations.find("root")->second;
    isCgi = false;
  }
}

bool  Request::setRouteAndVersion(const string &tmp) {
  route = firstWord(tmp);
  version = lastWord(tmp);
  if (version.compare("HTTP/1.1"))
    return (true);
  return(false);
}

void  Request::parserData(void) {
  int pos = header.find_first_of('\n');

  // set route and version
  if (setRouteAndVersion(trim(lastWord(header.substr(0, pos))))) {
    logger.Log("error version");
  }
  // set location:
  setLocation();
  // set method
  if (setMethod(trim(firstWord(header.substr(0, pos))))) {
    logger.Log("error method no allowed");
  }
  if (isCgi) {
    logger.Log("hay que lanzar cgi para esta location");
  }
}

void  Request::serverToClient(const string &_header, size_t fd) {
  header = _header;
  parserData();
  string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
  if (header.find("3009") != string::npos) {
    if (::send(fd, response.data(), response.size(), 0) < 0)
      logger.Log("error al enviar [%d]", fd);
   return;
  }
  std::string redirect_response = "HTTP/1.1 301 Moved Permanently\r\n";
  redirect_response += "Location:" + locationRoot.getReturn().second  + "\r\n"; // Cambia la URL según sea necesario
  redirect_response += "Connection: close\r\n\r\n";
  /*std::string redirect_response = "HTTP/1.1 301 Moved Permanently\r\n";
   redirect_response += "Location: http:0.0.0.0:3008/nueva_pagina\r\n";
   redirect_response += "Connection: close\r\n\r\n";
  */
  if (::send(fd, redirect_response.data(), redirect_response.size(), 0) < 0)
    logger.Log("error al enviar [%d]", fd);
}
