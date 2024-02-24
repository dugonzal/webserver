/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/24 10:55:52 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/parser.hpp"
#include <ostream>

Parser::Parser(void) { }

Parser::~Parser(void) { }

Parser::Parser(const string &filename): fileName(filename) {
  ifstream   *file;
  string     buffer;

  file = openFile(fileName);
  assert(file->is_open() == true);

  while (getline(*file, buffer, '\n')) {
   // buffer = trim(buffer);
    if (buffer.empty() || buffer[0] == '#')
       continue;
    else if (buffer.find("include") != string::npos)
      readIncludeError(buffer.substr(buffer.find_first_of(" ") + 1));
    else
      data.push_back(buffer);
  }

  file->close();
  delete file;
  printData();
  setNservers();
  assert(file->is_open() == false);
}

void  Parser::printData(void) {
  for (unsigned int i = 0; i < data.size(); i++)
    cout << data[i] << endl;
}

// como no puedo copiar el objeto me toca retornar un puntero de ifstream
ifstream *Parser::openFile(const string &fdName) {
  ifstream  *file = new std::ifstream(fdName.data());
  string     buffer;

  if (file->bad() || file->fail() || file->eof()) {
    delete file;
    throw(logic_error("file no open"));
  }
  return (file);
}

void  Parser::readInclude(string fdFile) {
    std::ifstream *file;
    string   buffer;

    file = openFile(fdFile);
    while (getline(*file, buffer, '\n')) {
     // buffer = trim(buffer);
      if (buffer.empty() || buffer[0] == '#')
        continue;
      else
        data.push_back(buffer);
    }
    file->close();
    delete file;
}

void Parser::readIncludeError(string fileName) {
  if (fileName[fileName.size() - 1] == ';')
    fileName[fileName.size() - 1] = '\0';
  else
    throw(runtime_error("no termine en  \";\""));

  readInclude(fileName);
}

void  Parser::setNservers(void) {
  for (unsigned int i = 0; i < data.size(); i++)
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        nServers++;
  std::cout << nServers << std::endl;
}
