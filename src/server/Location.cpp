/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:52:57 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/19 10:32:32 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Location.hpp"

Location::Location(void): autoIndex(-1), \
  port(-1), clientBodySize(-1), isCgi(false) { }

Location::~Location(void) { }

Location::Location(const Location &copy): \
  root(copy.root), path(copy.path), index(copy.index), \
    autoIndex(copy.autoIndex), cgiPath(copy.cgiPath), \
      _return(copy._return), methods(copy.methods), \
        errorPages(copy.errorPages), host(copy.host), \
          port(copy.port), serverName(copy.serverName), \
            clientBodySize(copy.clientBodySize), isCgi(copy.isCgi), \
              alias(copy.alias) { }

Location &Location::operator=(const Location &copy) {
  if (this != &copy) {
    root = copy.root;
    path = copy.path;
    index = copy.index;
    autoIndex = copy.autoIndex;
    cgiPath = copy.cgiPath;
    methods = copy.methods;
    errorPages = copy.errorPages;
    host = copy.host;
    port = copy.port;
    serverName = copy.serverName;
    clientBodySize = copy.clientBodySize;
    isCgi = copy.isCgi;
    _return = copy._return;
    alias = copy.alias;
  }
  return (*this);
}

void  Location::setRoot(const string &_root) {
  if (!root.empty())
    logger.LogThrow("setRoot [%s]", _root.data());
  root = _root;
}

void  Location::setPath(const string &_path) {
  if (!path.empty())
    logger.LogThrow("setPath [%s]", _path.data());
  path = _path;
}

void  Location::setIndex(const string &_index) {
  if (!index.empty())
    logger.LogThrow("setIndex [%s]", _index.data());
  index = _index;
}

void  Location::setAutoIndex(const string &_autoIndex) {
  if (autoIndex != -1)
    logger.LogThrow("setAutoIndex [%s]", _autoIndex.data());
  else if (!_autoIndex.compare("true") or !_autoIndex.compare("on") \
    or !_autoIndex.compare("TRUE") or !_autoIndex.compare("ON"))
    autoIndex = true;
  else if (!_autoIndex.compare("false") or !_autoIndex.compare("off") \
    or !_autoIndex.compare("False") or !_autoIndex.compare("OFF"))
      autoIndex = false;
  else
    logger.LogThrow("autoIndex [%s]", _autoIndex.data());
}

void  Location::setCgiPath(const string &_cgiPath) {
  if (!cgiPath.empty())
    logger.LogThrow("setCgiPath [%s]", _cgiPath.data());
  cgiPath = _cgiPath;
  isCgi = true;
}

void  Location::setReturn(const string &return_) {
  if (!_return.second.empty())
    logger.LogThrow("setReturn [%s]", return_.data());
  _return.first = atoi(firstWord(return_).data());
  if (_return.first < 100 or _return.first > 505)
    logger.LogThrow("setErrorPages code not allowed [%s]", return_.data());
  _return.second = lastWord(return_);
}

void  Location::setMethods(const string &_methods) {
  istringstream iss(_methods);

  methods.clear();
  if (!methods.empty())
    logger.LogThrow("setMethods");
  while (iss) {
    string sub;
    iss >> sub;
    if (sub.empty())
      break;
    else if (sub.compare("GET") and sub.compare("POST") && sub.compare("DELETE"))
      logger.LogThrow(" methods no allowed [%s]", sub.data());
    methods.push_back(sub);
  }
}

void  Location::setErrorPages(const string &_errorPages) {
  size_t n = atoi(firstWord(_errorPages).data());

  if (n < 100 or n > 505 or errorPages.find(n) != errorPages.end())
    logger.LogThrow("setErrorPages code not allowed [%s]", _errorPages.data());
  else if (errorPages.find(n) != errorPages.end())
    logger.LogThrow("setErrorPages code already exists [%s]", _errorPages.data());
  errorPages.insert(make_pair(n, lastWord(_errorPages)));
}

void  Location::setListen(const string &_listen) {
  string  tmp;
  
  int pos = _listen.find_first_of(":");
  int n   = 0;

  if (!host.empty() or port != -1)
    logger.LogThrow("listen exists (", _listen.data());
  else if (pos > 6) {
    tmp  = _listen.substr(0, pos);
    n  = atoi(_listen.substr(pos + 1).data());
    if (!tmp.compare("localhost") or !tmp.compare("127.0.0.1"))
      host = "127.0.0.1";
    else
      host = tmp;
    if (n < 0 or n > 65535)
      logger.LogThrow("error port out range (",  _listen.data());
    else
      port = n;
  } else if (pos < 0) {
      port = atoi(_listen.data());
      host = "127.0.0.1";
    if (port < 1 or port > 65535)
      logger.LogThrow("error port out range (",  _listen.data() );
  } else
      logger.LogThrow("no puedo establecer listen ", _listen.data());
}

void  Location::setServerName(const string &_serverName) {
  if (!serverName.empty())
    logger.LogThrow("exist serverName [%s]", _serverName.data());
  serverName = _serverName;
}


void Location::setClientBodySize(const string& _clientBodySize) {
  stringstream num;
  stringstream size;

  if (clientBodySize != -1)
    logger.LogThrow("clientBodySize exists [%s]", _clientBodySize.data());
  for (size_t i = 0; i < _clientBodySize.size(); i++) {
    if (isdigit(_clientBodySize.data()[i]))
      num << _clientBodySize.data()[i];
    else
      size << _clientBodySize.data()[i];
  }
  if (_clientBodySize.size() > 11)
    logger.LogThrow("clientBodySize error [%s]", _clientBodySize.data());
  clientBodySize = atoi(num.str().data());
  if (size.str().size() > 1)
    logger.LogThrow("clientBodySize error [%s]: too many characters", _clientBodySize.data());
  if (!size.str().compare("m"))
    clientBodySize *= 1000000;
  else if (!size.str().compare("k"))
    clientBodySize *= 1000;
}

void  Location::setAlias(const string &_alias) {
  if (!alias.empty())
    logger.LogThrow("alias exists [%s]", _alias.data());
  alias = _alias;
}

Location  Location::clone(void) const {
  if (!path.compare("root") and port < 1)
    throw(runtime_error("errror tiene que haber port"));
  else if (!path.compare("root") and !alias.empty())
    throw(runtime_error("error no aceptamos un alias en el general"));
  else if ((isCgi and (index.empty() and !cgiPath.empty())) or (isCgi and !index.empty() and cgiPath.empty()))
    throw(runtime_error("error si hay index hay cgi"));
  return (*this);
}

const string Location::getPath(void) const { return (path); }

const string  Location::getRoot(void) const { return(root); }

const string  Location::getIndex(void) const { return(index); }

const string  Location::getCgiPath(void) const { return(cgiPath); }

int Location::getAutoIndex(void) const { return(autoIndex); }

bool  Location::getIsCgi(void) const { return(isCgi); }

const vector<string>  Location::getmethods(void) const {
  return(methods);
}

const pair<size_t, string>  Location::getReturn(void) const {
  return(_return);
}

map<size_t, string> &Location::getErrorPages(void) {
  return(errorPages);
}

const string  Location::getHost(void) const { return (host); }

int Location::getPort(void) const { return (port); }

const string  Location::getServerName(void) const { return (serverName); }

const string  &Location::getAlias(void) const { return(alias); }

long Location::getClientBodySize(void) const { return (clientBodySize); }

void  Location::clear(void) {
  root.clear();
  path.clear();
  index.clear();
  autoIndex = -1;
  cgiPath.clear();
  _return.first = 0;
  _return.second.clear();
  methods.clear();
  errorPages.clear();
  host.clear();
  port = -1;
  clientBodySize = -1;
  alias.clear();
  isCgi = false;
}

ostream &operator<<(ostream &os, const Location &copy) {
  os << "Location:" << endl << "host: " << copy.host << endl << "port: " \
  << copy.port << endl << "path: " << copy.getPath() << endl << "root: " \
  << copy.getRoot() << endl << "index: " << copy.getIndex() << endl \
  << "autoIndex: " << copy.getAutoIndex() << endl << "cgiPath: " \
  << copy.getCgiPath() << endl <<  endl << "methods: " \
  << copy.getmethods().size() << endl << "return: " \
  << copy.getReturn().second << endl << "errorPages: " \
<< "isCgi: " \
  << copy.getIsCgi() << endl << "alias: " << copy.getAlias() << endl;
  return (os);
}
