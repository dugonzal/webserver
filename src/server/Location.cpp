/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:52:57 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/19 18:47:16 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Location.hpp"

Location::Location(void): autoIndex(-1), port(-1), clientBodySize(-1) { }

Location::~Location(void) { }

Location::Location(const Location &copy): \
  root(copy.root), path(copy.path), index(copy.index), \
    autoIndex(copy.autoIndex), cgiPath(copy.cgiPath), cgiExt(copy.cgiExt), \
      methods(copy.methods),  errorPages(copy.errorPages),
        host(copy.host), port(copy.port), serverName(copy.serverName) { }

Location &Location::operator=(const Location &copy) {
  if (&copy != this) {
    root = copy.root;
    path = copy.path;
    index = copy.index;
    autoIndex = copy.autoIndex;
    cgiPath = copy.cgiPath;
    cgiExt  = copy.cgiExt;
    methods = copy.methods;
    errorPages = copy.errorPages;
    host = copy.host;
    port = copy.port;
    serverName = copy.serverName;
  }
  return (*this);
}

void  Location::setRoot(const string &_root) {
  if (!root.empty())
    throw(runtime_error("setRoot"));
  root = _root;
}

void  Location::setPath(const string &_path) {
  if (!path.empty())
    throw(runtime_error("setPath"));
  path = _path;
}

void  Location::setIndex(const string &_index) {
  if (!index.empty())
    throw(runtime_error("setIndex"));
  index = _index;
}

void  Location::setAutoIndex(const string &_autoIndex) {
  if (autoIndex != -1)
    throw(runtime_error("setAutoIndex"));
  else if (!_autoIndex.compare("true") || !_autoIndex.compare("on") \
    || !_autoIndex.compare("TRUE") || !_autoIndex.compare("ON"))
    autoIndex = true;
  else if (!_autoIndex.compare("false") || !_autoIndex.compare("off") \
    || !_autoIndex.compare("False") || !_autoIndex.compare("OFF"))
      autoIndex = false;
  else
    throw(runtime_error(string("autoIndex (") + string(_autoIndex + ")")));
}

void  Location::setCgiPath(const string &_cgiPath) {
  if (!cgiPath.empty())
    throw(runtime_error("setCgiPath"));
  cgiPath = _cgiPath;
}

void  Location::setReturn(const string &return_) {
  if (!_return.second.empty())
    throw(runtime_error("setReturn"));
  _return.first = atoi(firstWord(return_).data());
  if (_return.first < 100 || _return.first > 505)
    throw(runtime_error("setErrorPages code not allowed"));
  _return.second = lastWord(return_);
}

void  Location::setCgiExt(const string &_cgiExt) {
  if (!cgiExt.empty())
    throw(runtime_error("setCgiExt"));
  cgiExt = _cgiExt;
}

void  Location::setMethods(const string &_methods) {
  istringstream iss(_methods);

  if (!methods.empty())
    throw(runtime_error("setMethods"));
  while (iss) {
    string sub;
    iss >> sub;
    if (sub.empty())
      break;
    else if (sub.compare("GET") && sub.compare("POST") && sub.compare("DELETE"))
      throw(runtime_error(string(" methods no allowed (") + string(sub + ")")));
    methods.push_back(sub);
  }
}

void  Location::setErrorPages(const string &_errorPages) {
  size_t n = atoi(firstWord(_errorPages).data());

  if (n < 100 || n > 505)
    throw(runtime_error("setErrorPages code not allowed"));
  else if (errorPages.find(n) != errorPages.end())
    throw(runtime_error("setErrorPages code already exists"));
  errorPages.insert(pair<size_t, string>(n, lastWord(_errorPages)));
}

void  Location::setListen(const string &_listen) {
  int pos = _listen.find_first_of(":");
  int n = 0;
  string  tmp;
// habria que comprobar que el host tengo 4 puntos y sean mayores a 0 y < 255
  if (!host.empty() || port != -1)
    throw(runtime_error(string("listen exists (") + string(_listen + ")")));
  else if (pos > 6) {
    tmp  = _listen.substr(0, pos);
    n  = atoi(_listen.substr(pos + 1).data());
    if (!tmp.compare("localhost") || !tmp.compare("127.0.0.1"))
      host = "0.0.0.0";
    else
      host = tmp;
    if (n < 0 or n > 65535)
      throw(runtime_error(string("error port out range (") + string(_listen + ")")));
    else
      port = n;
  } else if (pos < 0) {
    if (n < 1 or n > 65535)
      throw(runtime_error(string("error port out range (") + string(_listen + ")")));
    else
      port = atoi(_listen.data());
  } else
      throw(runtime_error(string("no puedo establecer listen (") + string(_listen + ")")));
}

void  Location::setServerName(const string &_serverName) {
  if (!serverName.empty())
    throw(runtime_error("exist serverName"));
  serverName = _serverName;
}


void Location::setClientBodySize(const string& _clientBodySize) {
  stringstream num;
  stringstream size;
  int ret;

  if (clientBodySize != -1)
    throw(runtime_error(string("clientBodySize exists ("+ string(_clientBodySize + ")"))));
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
  clientBodySize = ret;
}

// hay que setear default posiblemente
Location  Location::clone(void) const {
  if ((!cgiPath.empty() and cgiExt.empty()) \
    or (cgiPath.empty() and !cgiExt.empty()))
      throw(runtime_error("si hay cgi tiene que haber path y ext"));
  else if (!path.compare("root") && port < 1)
      throw(runtime_error("errror tiene que haber port"));
    return (*this);
}

const string Location::getPath(void) const { return (path); }

const string  Location::getRoot(void) const { return(root); }

const string  Location::getIndex(void) const { return(index); }

const string  Location::getCgiPath(void) const { return(cgiPath); }

const string  Location::getCgiext(void) const { return(cgiExt); }

int Location::getAutoIndex(void) const { return(autoIndex); }

const vector<string>  Location::getmethods(void) const {
  return(methods);
}

const pair<size_t, string>  Location::getReturn(void) const {
  return(_return);
}

const map<size_t, string> Location::getErrorPages(void) const {
  return(errorPages);
}

const string  Location::getHost(void) const { return (host); }

int Location::getPort(void) const { return (port); }

const string  Location::getServerName(void) const { return (serverName); }

void  Location::clear(void) {
  root.clear();
  path.clear();
  index.clear();
  autoIndex = -1;
  cgiPath.clear();
  cgiExt.clear();
  _return.first = 0;
  _return.second.clear();
  methods.clear();
  errorPages.clear();
  host.clear();
  port = -1;
  clientBodySize = -1;
}

ostream &operator<<(ostream &os, const Location &copy) {
  os << "Location:" << endl << "host: " << copy.host << endl << "port: " \
  << copy.port << endl << "path: " << copy.getPath() << endl << "root: " \
  << copy.getRoot() << endl << "index: " << copy.getIndex() << endl \
  << "autoIndex: " << copy.getAutoIndex() << endl << "cgiPath: " \
  << copy.getPath() << endl << "cgiExt: " << copy.getCgiext() \
  <<  endl << "methods: " << copy.getmethods().size() << endl \
  << "return: " << copy.getReturn().second << endl \
  << "errorPages: " << copy.getErrorPages().size() << endl;
  return (os);
}
