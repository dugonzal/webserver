/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:52:57 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/24 14:44:09 by Dugonzal         ###   ########.fr       */
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
