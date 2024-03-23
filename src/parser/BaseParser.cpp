/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/23 12:23:49 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/BaseParser.hpp"

BaseParser::BaseParser(void) { }

BaseParser::~BaseParser(void) { }

BaseParser::BaseParser(const BaseParser &copy): \
  fileName(copy.fileName), nServers(copy.nServers), data(copy.data) { }

BaseParser &BaseParser::operator=(const BaseParser &copy) {
  if (this != &copy) {
    fileName = copy.fileName;
    nServers = copy.nServers;
    data = copy.data;
  }
  return (*this);
}

BaseParser::BaseParser(const string &filename): fileName(filename) {
  ifstream   *file;
  string     buffer;

  file = openFile(fileName);
  if (!file) {
    delete file;
    throw(runtime_error("file not found"));
  }
  while (getline(*file, buffer, '\n')) {
    buffer = trim(buffer);
    if (skipLine(buffer))
       continue;
    else if (buffer.find("include") != string::npos) {
      if (readIncludeError(buffer.substr(buffer.find_last_of(" ") + 1))) {
        delete file;
        throw(runtime_error("include error"));
      }
    }
    else
      data.push_back(buffer);
  }
  delete file; // el destructor de ifstream cierra el file
  setNservers();
  checkSemicolon();
  handlerScopeLocation();
  // printData(data);
}

void  BaseParser::printData(const std::vector<string> &tmp) const {
  for (unsigned int i = 0; i < tmp.size(); i++)
    cout << tmp[i] << endl;
}

// como no puedo copiar el objeto me toca retornar un puntero de ifstream
ifstream  *BaseParser::openFile(const string &fdName) const {
  ifstream  *file;
  string    buffer;

  file = new ifstream(fdName.data());
  if (file->bad() || file->fail() || file->eof()) {
    delete file;
    return (NULL);
  }
  return (file);
}

bool  BaseParser::readInclude(const string &fdFile) {
  ifstream *file;
  string   buffer;

  file = openFile(fdFile);
  if (!file) {
    delete file;
    return (true);
  }
  while (getline(*file, buffer, '\n')) {
    buffer = trim(buffer);
    if (skipLine(buffer))
      continue;
    else
      data.push_back(buffer);
  }
  delete file;
  return (false);
}

bool  BaseParser::readIncludeError(string fileName) {
  if (fileName[fileName.size() - 1] == ';')
    fileName[fileName.size() - 1] = '\0';
  else
    return (true);
  if (readInclude(fileName))
    return (true);
  return (false);
}

void  BaseParser::setNservers(void) {
  std::size_t endServer = 0;

  nServers = 0;
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

int  BaseParser::getNservers(void) const { return(nServers); }

std::vector<string> BaseParser::getData(void) const { return(data); }

int BaseParser::serverError(unsigned int i) const {
  while (i < data.size()) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        throw(runtime_error("server dentro de server"));
    else if (data[i].find("include") != string::npos)
      throw(runtime_error("include circular"));
    else if (data[i].find("};") != string::npos)
      break;
    i++;
  }
  return (i);
}

void  BaseParser::handlerScopeError(void) {
  for (unsigned int i = 0; i < data.size(); i++)
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        i = serverError(++i);
    else
      throw(runtime_error("fuera del scope del server"));
}

int     BaseParser::parserScopeLocation(unsigned int j) const {
  if (data[j].find("{") == string::npos \
    || data[j].find_first_of("/") == string::npos)
      throw(runtime_error("scope location"));

  while (++j < data.size()) {
    if (data[j].find("}") != string::npos)
      break;
    else if (data[j].find("location") != string::npos)
      throw(runtime_error("parser location"));
  }
  return(j);
}

void  BaseParser::checkSemicolon(void) const {
  for (unsigned int i = 0; i < data.size(); i++) {
    if (data[i].find("{") != string::npos \
      || data[i].find("}") != string::npos)
        continue;
    else if (data[i][data[i].size() - 1] != ';')
      throw(runtime_error("no termina en semicolon"));
  }
}

void  BaseParser::handlerScopeLocation(void) {
    int lo = 0;
    int end = 0;
  for (unsigned int i = 0; i < data.size(); i++) {
    if (data[i].find("location") != string::npos && ++lo)
      parserScopeLocation(i);
    else if ((data[i].find("}") != string::npos) \
      && (data[i].size() == 1))
        end++;
  }
  if (lo != end)
    throw(runtime_error("location"));
}
