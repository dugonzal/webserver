/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/26 18:42:17 by Dugonzal         ###   ########.fr       */
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
      readIncludeError(buffer.substr(buffer.find_last_of(" ") + 1));
    else
      data.push_back(buffer);
  }
  delete file; // el destructor de ifstream cierra el file
  setNservers();
  checkSemicolon();
  handlerScopeLocation();
  printData();
}

void  Parser::printData(void) const {
  for (unsigned int i = 0; i < data.size(); i++)
    cout << data[i] << endl;
}

// como no puedo copiar el objeto me toca retornar un puntero de ifstream
ifstream  *Parser::openFile(const string &fdName) const {
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

std::vector<string> Parser::getData(void) const { return(data); }

void  Parser::serverError(unsigned int *j) const {
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

void  Parser::checkSemicolon(void) const {
  for (unsigned int i = 0; i < data.size(); i++) {
    if (data[i].find("{") != string::npos \
      || data[i].find("}") != string::npos)
        continue;
    else if (data[i][data[i].size() - 1] != ';')
      throw(runtime_error("error no termina en semicolon"));
  }
}

int     Parser::parserScopeLocation(unsigned int j) {
  if (data[j].find("{") == string::npos \
    || data[j].find_first_of("/") == string::npos)
      throw(runtime_error("error scope location"));

  while (++j < data.size()) {
    if (data[j].find("}") != string::npos)
      break;
    else if (data[j].find("location") != string::npos)
      throw(runtime_error("error parser location"));
  }
  return(j);
}

void  Parser::handlerScopeLocation(void) {
  for (unsigned int i = 0; i < data.size(); i++)
    if (data[i].find("location") != string::npos)
      parserScopeLocation(i);
}

