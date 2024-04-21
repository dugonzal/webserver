/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 17:57:07 by jaizpuru         ###   ########.fr       */
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

const Logger  &BaseParser::getLogger(void) const { return(logger); }

void  BaseParser::setWords(void) {
  words.insert("server");
  words.insert("location");
  words.insert("include");
  words.insert("server_name");
  words.insert("listen");
  words.insert("index");
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
    logger.Log("file not found [%s]", filename.data());
    throw(runtime_error(""));
  }
  setWords();
  while (getline(*file, buffer, '\n')) {
    buffer = trim(buffer);
    if (skipLine(buffer))
       continue;
    if (!checkAllowedWords(firstWord(buffer))) {
      delete file;
      logger.Log("Word not allowed: [%s]", buffer.data());
      throw(runtime_error(string("")));
    }
    if (!firstWord(buffer).compare("include")) {
      if (readIncludeError(lastWord(buffer))) {
        delete file;
        logger.Log("include error [%s]", buffer.data());
        throw(runtime_error(""));
      }
      continue;
    }
    data.push_back(buffer);
  }
  delete file;
  deleteServerEmpty();
  setNservers();
  checkSemicolon();
  keyValueCkeck();
  handlerScopeLocation();
}

void  BaseParser::deleteServerEmpty(void) {
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos) {
        if (data[i + 1].find("};") != string::npos) {
          data.erase(data.begin() + i, data.begin() + i + 2);
          i--;
        }
    }
  }
}

void  BaseParser::keyValueCkeck(void) {
  for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
    string::iterator end = it->end() - 1;
    if (it->find("{") != string::npos \
      || it->find("}") != string::npos)
        continue;
    if (*end == ';') {
      it->erase(end);
      if (!lastWord(*it).size()) {
        logger.Log("missing key or value [%s]", trim(*it).data());
        throw(runtime_error(""));
      }
      size_t n = numberWords(*it);
      if (n > 2) {
        string tmp = firstWord(*it);
        if ((n == 3 && (!tmp.compare("error_page") \
          || !tmp.compare("return")))) {
          continue;
        } else if (n < 5 && !tmp.compare("allow_methods")) {
          continue;
        } else {
          logger.Log("too many words [%s]", trim(*it).data());
          throw(runtime_error(""));
        }
      }
    }
  }
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

const vector<string> BaseParser::getData(void) const { return(data); }

size_t  BaseParser::skipLocation(size_t i) {
  while (++i < data.size())
    if (!data[i].compare("}"))
      break;
  return (i);
}

size_t  BaseParser::serverError(size_t i) {
  while (++i < data.size()) {
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
    } else if (!data[i].compare("};")) {
      break;
    }
  }
  return (i);
}

void  BaseParser::handlerScopeError(void) {
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i].find("server") != string::npos \
      && data[i].find("{") != string::npos)
        i = serverError(i);
    else
      throw(runtime_error(string("fuera del scope del server ") \
        + string(data[i])));
  }
}

size_t BaseParser::parserScopeLocation(size_t j) const {
  string  tmp = lastWord(data[j]);
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
