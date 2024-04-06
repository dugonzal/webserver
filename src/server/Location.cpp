/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:52:57 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/06 13:46:31 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Location.hpp"

Location::Location(void): autoIndex(-1) { }

Location::~Location(void) { }

Location::Location(const Location &copy): \
  root(copy.root), path(copy.path), index(copy.index), \
    autoIndex(copy.autoIndex), cgiPath(copy.cgiPath), cgiExt(copy.cgiExt), \
      methods(copy.methods),  errorPages(copy.errorPages) { }

Location &Location::operator=(const Location &copy) {
  if (&copy != this) {
    cout << "copia locations" << endl;
    root = copy.root;
    path = copy.path;
    index = copy.index;
    autoIndex = copy.autoIndex;
    cgiPath = copy.cgiPath;
    cgiExt  = copy.cgiExt;
    methods = copy.methods;
    errorPages = copy.errorPages;
  }
  return (*this);
}

void  Location::setRoot(const string &_root) {
  if (!root.empty())
    throw(runtime_error("setRoot"));
  root = _root;
}

// basicamente si se establece dos veces en un
// alcance de location es un error porque no podemos
// definir dos veces lo mismo
void  Location::setPath(const string &_path) {
  if (!path.empty())
    throw(runtime_error("setPath"));
  path = _path;
}

void  Location::setIndex(const string &_index) {
  cout << "setIndex " << _index << endl;
  if (!index.empty())
    throw(runtime_error("setIndex"));
  cout << !index.empty() << " -  " << _index << endl;
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
  if (errorPages.find(n) != errorPages.end())
    throw(runtime_error("setErrorPages code already exists"));
  errorPages.insert(pair<size_t, string>(n, lastWord(_errorPages)));
}

Location  Location::clone(void) const {
  // antes de copiar la location podemos dejar valores por default
  // o a null para facilitar el uso de la location
  return (*this);
}

const string Location::getPath(void) const { return (path); }

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
}

ostream &operator<<(ostream &os, const Location &copy) {
  os << "path: " << copy.getPath() << endl;
  return (os);
}
