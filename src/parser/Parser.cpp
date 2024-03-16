/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:19 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 13:13:58 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/Parser.hpp"

Parser::Parser(void) { }

Parser::~Parser(void) { }

Parser::Parser(const string &filename): BaseParser(filename) {
  dataServers = new vector<string>*[nServers];

  for (unsigned int i = 0; i < nServers; i++)
    dataServers[i] = new vector<string>;
  splitServers();
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

unsigned int  Parser::getServer(int n, unsigned int j) {
  while (++j < data.size()) {
    if (data[j].find("};") != string::npos)
      break;
    dataServers[n]->push_back(cleanSemiColon(data[j]));
  }
  return (j);
}

void  Parser::splitServers(void) {
  unsigned int n = 0;
  for (unsigned int i = 0; i < data.size(); i++) {
    i = getServer(n++, i);
    if (n == nServers)
      break;
  }
}

vector<string> **Parser::getDataServers(void) const { return(dataServers); }
