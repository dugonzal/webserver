/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:08 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/11 11:26:21 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Utils.hpp"

bool  skipLine(const string &line) {
  if (line.empty() || line[0] == '#')
      return(true);
  return(false);
}

string  firstWord(string line) {
  size_t pos = line.find_first_of(WHITESPACES);

  if (pos == string::npos)
    return (line);

  return (line.substr(0, pos));
}

string  lastWord(string line) {
  size_t pos = line.find_first_of(WHITESPACES);

  if (pos == string::npos)
    return ("");

  return (trim(line.substr(pos)));
}

string trim(const string &line) {
  size_t first = line.find_first_not_of(WHITESPACES);

  if (first == string::npos)
    return ("");

  size_t last = line.find_last_not_of(WHITESPACES);

  return (line.substr(first, ((last - first) + 1)));
}

bool isW(const char c) {
  for (size_t i = 0; i < strlen(WHITESPACES) ; i++)
    if (WHITESPACES[i] == c)
    return (true);
  return (false);
}

size_t  numberWords(const string  &line) {
  size_t  count = 0, i = 0;

  while (i < line.size()) {
    if (!isW(line[i])) {
      count++;
      while (i < line.size() && !isW(line[i]))
        i++;
    }
    i++;
  }
  return (count);
}

string  readFile(const string &filename) {
  ifstream file(filename.data());
  ostringstream oss;

  if (!file.is_open()) {
      cerr << "Failed to open file: " << filename << endl;
      return ("");
  }
  oss << file.rdbuf();
  return (oss.str());
}

void  readDirectory(const string &path) {
  struct dirent *ent;
  DIR *dir;

  if (path.empty()) {
    cerr << "error es impty file" << endl;
    return;
  }
  if ((dir = opendir(path.data())) != NULL) {
    while ((ent = readdir(dir)) != NULL)
      cout << ent->d_name << endl;
  }
  closedir(dir);
}

bool isDirectory(const string &path) {
  struct stat s;

  if (!stat(path.data(), &s))
    return S_ISDIR(s.st_mode);
  return false;
}

bool isFile(const string &path) {
  struct stat s;

  if (!stat(path.data(), &s))
    return S_ISREG(s.st_mode);
  return false;
}

ifstream  *openFile(const string &fdName) {
  ifstream  *file;
  string    buffer;

  file = new ifstream(fdName.data());
  if (file->bad() || file->fail() || file->eof()) {
    delete file;
    return (NULL);
  }
  return (file);
}

string convertHTML(const vector<string>& cgiOutput) {
  string htmlCode;
  htmlCode += "<html>\r<head>\n\r</head>\n\r\r<body>\n";
  for (size_t it = 0; it < cgiOutput.size(); it++) {
    htmlCode += "\r\r\r<div>" + cgiOutput[it] + "</div>\n";
  }
  htmlCode += "\r\r</body>\n</html>";
  return htmlCode;
}

string generate_random_session_id() {
  stringstream ss;
  int length = 10;
  const string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  for (int i = 0; i < length; ++i)
      ss << alphanum[rand() % alphanum.length()];

  return ss.str();
}
