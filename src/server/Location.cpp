/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:52:57 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/24 15:51:00 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Location.hpp"

Location::Location(void): root("resources"), path("/"), index("index.html"), \
  autoIndex(false), cgiPath("None") { }

Location::~Location(void) { }

Location::Location(const Location &copy): \
  root(copy.root), path(copy.path), index(copy.index), \
    autoIndex(copy.autoIndex), cgiPath(copy.cgiPath), methods(copy.methods),
      errorPages(copy.errorPages) { }

Location &Location::operator=(const Location &copy) {
  if (&copy != this) {
    root = copy.root;
    path = copy.path;
    index = copy.index;
    autoIndex = copy.autoIndex;
    cgiPath = copy.cgiPath;
    methods = copy.methods;
    errorPages = copy.errorPages;
  }
  return (*this);
}

void  Location::setRoot(const string &_root) {
  root = _root;
}

void  Location::setPath(const string &_path) {
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

void  Location::setMethods(const string &_methods) {
  methods.push_back(_methods);
}

void  Location::setErrorPages(const int &n, const string &_errorPages) {
  errorPages.insert(std::make_pair<int, string>(n, _errorPages));
}

Location  Location::clone(void) {
  return (*this);
}
