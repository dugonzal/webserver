/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/04 19:40:11 by Dugonzal         ###   ########.fr       */
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
  words.insert("}");
  words.insert("};");
}

bool  BaseParser::checkAllowedWords(const string &line) const {
  if (words.find(line) != words.end())
    return (true);
  return (false);
}

BaseParser::BaseParser(const string &filename): fileName(filename) {
  ifstream   *file;
  string     buffer;

  if (!(file = openFile(fileName))) {
    delete file;
    throw(runtime_error(string("file not found (") + string(fileName + ")")));
  }
  setWords();
  while (getline(*file, buffer, '\n')) {
    buffer = trim(buffer);
    if (skipLine(buffer))
       continue;
    if (!checkAllowedWords(firstWord(buffer))) {
      delete file;
      throw(runtime_error(string("Word not allowed: (" + string(buffer + ")"))));
    }
    if (!firstWord(buffer).compare("include")) {
      if (readIncludeError(lastWord(buffer))) {
        delete file;
        throw(runtime_error(string("include error (") + string(buffer + ")")));
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
  for (size_t i = 0; i < tmp.size(); i++)
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

  if (!(file = openFile(fdFile))) {
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
    fileName.erase(fileName.size() - 1);
  else
    return (true);
  if (readInclude(fileName))
    return (true);
  return (false);
}

void  BaseParser::setNservers(size_t nS) { nServers = nS; }

void  BaseParser::setNservers(void) {
  size_t endServer = 0;

  nServers = 0;
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        nServers++;
    else if (!data[i].compare("};"))
      endServer++;
  }
  if (nServers != endServer)
    throw(runtime_error("scope server "));
  else
    handlerScopeError();
}

size_t  BaseParser::getNservers(void) const { return(nServers); }

vector<string> BaseParser::getData(void) const { return(data); }

size_t  BaseParser::skipLocation(size_t i) {
  while (++i < data.size())
    if (!data[i].compare("}"))
      break;
  return (i);
}

size_t  BaseParser::serverError(size_t i) {
  while (i < data.size()) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        throw(runtime_error("server dentro de server"));
    else if (!firstWord(data[i]).compare("include"))
      throw(runtime_error("include circular"));
    else if (!firstWord(data[i]).compare("cgi_path") \
      || !firstWord(data[i]).compare("cgi_ext"))
        throw(runtime_error(string("defined in global scope (")  + string(data[i] + ")")));
    else if (data[i].find("location") != string::npos \
     && data[i].find("{") != string::npos) {
        i = skipLocation(i);
        continue;
    }
    else if (!data[i].compare("};"))
      break;
    i++;
  }
  return (i);
}

void  BaseParser::handlerScopeError(void) {
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        i = serverError(++i);
    else
      throw(runtime_error(string("fuera del scope del server ") \
        + string(data[i])));
  }
}

size_t BaseParser::parserScopeLocation(size_t j) const {
  string tmp = lastWord(data[j]);

  if (tmp[0] != '/')
    throw(runtime_error(string("scope location missing / (") + string(data[j] + ")")));
  else if (data[j].find("{") == string::npos)
      throw(runtime_error("scope location"));
  while (++j < data.size()) {
    if (!data[j].compare("}"))
      break;
    else if (!firstWord(data[j]).compare("server_name"))
        throw(runtime_error(string("parser location (") + string(data[j] + ")")));
    else if (!firstWord(data[j]).compare("server"))
      throw(runtime_error(string("parser location (") + string(data[j] + ")")));
    else if (!firstWord(data[j]).compare("location"))
      throw(runtime_error(string("parser location (") + string(data[j] + ")")));
    else if (!firstWord(data[j]).compare("listen"))
      throw(runtime_error(string("parser location (") + string(data[j] + ")")));
  }
  return(j);
}

void  BaseParser::checkSemicolon(void) const {
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i].find("{") != string::npos \
      || !data[i].compare("}"))
        continue;
    else if (data[i][data[i].size() - 1] != ';')
      throw(runtime_error("no termina en semicolon"));
  }
}

void  BaseParser::handlerScopeLocation(void) {
  int lo = 0, end = 0;
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i].find("location") != string::npos \
      && data[i].find("{") != string::npos && ++lo)
        parserScopeLocation(i);
    else if ((!data[i].compare("}")))
        end++;
  }
  if (lo != end)
    throw(runtime_error(string("Location scope not properly") \
      + string("closed: Check brace matching.")));
}
