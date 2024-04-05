/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:52:57 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/04 21:54:40 by Dugonzal         ###   ########.fr       */
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
  index = _index;
}

void  Location::setAutoIndex(const bool &_autoIndex) {
  autoIndex = _autoIndex;
}

void  Location::setCgiPath(const string &_cgiPath) {
  cgiPath = _cgiPath;
}

void  Location::setCgiExt(const string &_cgiExt) {
  cgiExt = _cgiExt;
}
void  Location::setMethods(const string &_methods) {
  methods.push_back(_methods);
}

void  Location::setErrorPages(const int &n, const string &_errorPages) {
  errorPages.insert(std::pair<int, string>(n, _errorPages));
}

Location  Location::clone(void) const {
  return (*this);
}

ostream &operator<<(ostream &os, const Location &copy) {
  os << "" << endl;
  (void)copy;
  return (os);
}
