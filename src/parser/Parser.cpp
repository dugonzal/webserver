/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:19 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/06/02 21:17:31 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/Parser.hpp"

Parser::Parser(void) { }

Parser::~Parser(void) {
  delete [] dataServers;
}

Parser::Parser(const string &filename): BaseParser(filename) {
  dataServers = new vector<string>[nServers];
  size_t i = -1;

  for (vector<string>::iterator it = data.begin(); \
    it not_eq data.end() && ++i < nServers; it++) {
    if (it->find("server") not_eq string::npos \
      && it->find("{") not_eq string::npos) {
        while (++it not_eq data.end() && it->find("};") == string::npos)
          dataServers[i].push_back(*it);
    }
  }
}

Parser::Parser(const Parser &copy): BaseParser(copy), \
  dataServers(copy.dataServers) { }

Parser &Parser::operator=(const Parser &copy) {
  if (this not_eq &copy) {
    BaseParser::operator=(copy);
    dataServers = copy.dataServers;
  }
  return (*this);
}

const vector<string> *Parser::getDataServers(void) const {
  return (dataServers);
}
