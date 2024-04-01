/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:19 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/01 18:06:51 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/Parser.hpp"
#include <cstddef>

Parser::Parser(void) { }

Parser::~Parser(void) { delete [] dataServers; }

Parser::Parser(const string &filename): BaseParser(filename) {
  dataServers = new vector<string>[nServers];
  size_t i = -1;

  for (vector<string>::const_iterator it = data.begin(); \
    it != data.end() && ++i < nServers; it++) {
      if (it->find("server") != string::npos) {
        while (++it != data.end() && it->find("};") == string::npos)
          dataServers[i].push_back(*it);
      }
  }
}

Parser::Parser(const Parser &copy): BaseParser(copy), \
  dataServers(copy.dataServers) { }

Parser &Parser::operator=(const Parser &copy) {
  if (this != &copy) {
    BaseParser::operator=(copy);
    dataServers = copy.dataServers;
  }
  return (*this);
}

vector<string> *Parser::getDataServers(void) const { return (dataServers); }
