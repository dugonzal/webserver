/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/31 15:36:29 by Dugonzal         ###   ########.fr       */
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

void  BaseParser::setWords(void) {
  words.insert("index");
  words.insert("server");
  words.insert("location");
  words.insert("include");
  words.insert("server_name");
  words.insert("listen");
  words.insert("return");
  words.insert("root");
  words.insert("autoindex");
  words.insert("client_max_body_size");
  words.insert("error_page");
  words.insert("cgi_path");
  words.insert("cgi_ext");
  words.insert("allow_methods");
}

bool  BaseParser::checkWords(const string &line) const {
  if (line == "}" || line == "};")
    return (false);
  else if (words.find(line) == words.end())
    return (true);
  return (false);
}

BaseParser::BaseParser(const string &filename): fileName(filename) {
  ifstream   *file;
  string     buffer;

  setWords();
  file = openFile(fileName);
  if (!file) {
    delete file;
    throw(runtime_error("file not found"));
  }
  while (getline(*file, buffer, '\n')) {
    buffer = trim(buffer);
    if (skipLine(buffer))
       continue;
    if (checkWords(firstWord(buffer))) {
      delete file;
      throw(runtime_error(string("checkWords " + string(buffer))));
    }
    if (buffer.find("include") != string::npos) {
      if (readIncludeError(buffer.substr(buffer.find_last_of(" ") + 1))) {
        delete file;
        throw(runtime_error("include error"));
      }
      continue;
    }
    data.push_back(buffer);
  }
  delete file;
  setNservers();
  checkSemicolon();
  handlerScopeLocation();
}

void  BaseParser::printData(const vector<string> &tmp) const {
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
  size_t endServer = 0;

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

vector<string> BaseParser::getData(void) const { return(data); }

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
  for (unsigned int i = 0; i < data.size(); i++) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        i = serverError(++i);
    else
      throw(runtime_error(string("fuera del scope del server ") + string(data[i])));
  }
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
  int lo = 0, end = 0;
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
