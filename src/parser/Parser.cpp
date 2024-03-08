/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:19 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/08 03:11:32 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/Parser.hpp"

Parser::Parser(void) { }

Parser::~Parser(void) {
  for (unsigned int i = 0; i < nServers; i++)
    delete dataServers[i];
  delete [] dataServers;
}

Parser::Parser(const string &filename): BaseParser(filename) {
  
  dataServers = new vector<string>*[nServers];
 
  for (unsigned int i = 0; i < nServers; i++)
    dataServers[i] = new vector<string>;

  splitServers() ;
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

unsigned int  Parser::getServer(int nServer, unsigned int j) {

  cout  << "  "  << nServer << endl;
  while (++j < data.size()) {
    if (data[j].find("};") != string::npos)
      break;
    dataServers[nServer]->push_back(data[j]);
    data[j] = ""; 
  }
  return (j);
}

void  Parser::splitServers(void) {

  unsigned int n = 0;
  for (unsigned int i = 0; i < data.size(); i++) { 
    cout << endl;
    if (n == nServers)
      break;
    i = getServer(++n, i);
  }
  for (unsigned int j = 0; j < nServers; j++) 
    for (unsigned int i = 0; i < dataServers[j]->size(); i++) 
    cout << dataServers[j]->at(i) << endl << endl;
}
