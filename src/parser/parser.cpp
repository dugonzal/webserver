/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/25 20:20:47 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/parser.hpp"

Parser::Parser(void) { }

Parser::~Parser(void) { }

Parser::Parser(const string &filename): fileName(filename) {
  ifstream   *file;
  string     buffer;

  file = openFile(fileName);
  while (getline(*file, buffer, '\n')) {
    buffer = trim(buffer);
    if (buffer.empty() || buffer[0] == '#')
       continue;
    else if (buffer.find("include") != string::npos)
      readIncludeError(buffer.substr(buffer.find_first_of(" ") + 1));
    else
      data.push_back(buffer);
  }
  delete file; // el destructor de ifstream cierra el file
  setNservers();
  printData();
}

void  Parser::printData(void) {
  for (unsigned int i = 0; i < data.size(); i++)
    cout << data[i] << endl;
}

// como no puedo copiar el objeto me toca retornar un puntero de ifstream
ifstream  *Parser::openFile(const string &fdName) {
  ifstream  *file;
  string    buffer;

  file = new ifstream(fdName.data());
  if (file->bad() || file->fail() || file->eof()) {
    delete file;
    throw(logic_error("file no open"));
  }
  return (file);
}

void  Parser::readInclude(const string &fdFile) {
  ifstream *file;
  string   buffer;

  file = openFile(fdFile);
  while (getline(*file, buffer, '\n')) {
    buffer = trim(buffer);
    if (buffer.empty() || buffer[0] == '#')
      continue;
    else
      data.push_back(buffer);
  }
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
  std::size_t endServer;

  endServer = 0;
  for (unsigned int i = 0; i < data.size(); i++) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        nServers++;
    else if (data[i].find("};") != string::npos)
          endServer++;
  }
  if (nServers != endServer)
    throw(runtime_error("scope server"));
  else
    handlerScopeError();
}

int  Parser::getNservers(void) const { return(nServers); }

void  Parser::serverError(unsigned int *j) {
  for (unsigned int i = *j; i < data.size(); i++) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        throw(runtime_error("server dentro de server"));
    else if (data[i].find("include") != string::npos)
        throw(runtime_error("include circular"));
    else if (data[i].find("};") != string::npos)
        break;
  }
}

void  Parser::handlerScopeError(void) {
  for (unsigned int i = 0; i < data.size(); i++)
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        serverError(&++i);
}
