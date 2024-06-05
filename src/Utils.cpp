/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:08 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/06/02 21:16:06 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Utils.hpp"

bool  Utils::skipLine(const string &line) {
  if (line.empty() || line[0] == '#')
      return(true);
  return(false);
}

string  Utils::firstWord(string line) {
  size_t pos = line.find_first_of(WHITESPACES);

  if (pos == string::npos)
    return (line);

  return (line.substr(0, pos));
}

string  Utils::lastWord(string line) {
  size_t pos = line.find_first_of(WHITESPACES);

  if (pos == string::npos)
    return ("");

  return (trim(line.substr(pos)));
}

string Utils::trim(const string &line) {
  size_t first = line.find_first_not_of(WHITESPACES);

  if (first == string::npos)
    return ("");

  size_t last = line.find_last_not_of(WHITESPACES);

  return (line.substr(first, ((last - first) + 1)));
}

bool Utils::isW(const char c) {
  for (size_t i = 0; i < strlen(WHITESPACES) ; i++)
    if (WHITESPACES[i] == c)
    return (true);
  return (false);
}

size_t  Utils::numberWords(const string  &line) {
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

string  Utils::readFile(const string &filename) {
  ifstream file(filename.data());
  ostringstream oss;

  if (!file.is_open()) {
      cerr << "Failed to open file: " << filename << endl;
      return ("");
  }
  oss << file.rdbuf();
  return (oss.str());
}

void  Utils::readDirectory(const string &path) {
  struct dirent *ent;
  DIR *dir;

  if (path.empty()) {
    cerr << "error es impty file" << endl;
    return;
  }
  if ((dir = opendir(path.data())) not_eq NULL) {
    while ((ent = readdir(dir)) not_eq NULL)
      cout << ent->d_name << endl;
  }
  closedir(dir);
}

bool Utils::isDirectory(const string &path) {
  struct stat s;

  if (!stat(path.data(), &s))
    return S_ISDIR(s.st_mode);
  return false;
}

bool Utils::isFile(const string &path) {
  struct stat s;

  if (!stat(path.data(), &s))
    return S_ISREG(s.st_mode);
  return false;
}

ifstream  *Utils::openFile(const string &fdName) {
  ifstream  *file;
  string    buffer;

  file = new ifstream(fdName.data());
  if (file->bad() || file->fail() || file->eof()) {
    delete file;
    return (NULL);
  }
  return (file);
}

string Utils::convertHTML(const string& cgiOutput) {
  string        htmlCode;
  stringstream  cgiLine;
  htmlCode += "<html>\r<head>\n\r</head>\n\r\r<body>\n";
  for (size_t it = 0; cgiOutput[it]; it++) {
    if (cgiOutput[it] == '\n') {
      htmlCode += "\r\r\r<div>" + cgiLine.str() + "</div>\n";
      cgiLine.str("");
    }
    else
      cgiLine << cgiOutput[it];
  }
  htmlCode += "\r\r</body>\n</html>";
  return htmlCode;
}

string Utils::generate_random_session_id(size_t length) {
  const string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  stringstream ss;

  for (size_t i = 0; i < length; ++i)
      ss << alphanum[rand() % alphanum.length()];

  return ss.str();
}

void	Utils::killProcess(int _pid) {
	kill(_pid, SIGTERM);

	bool died = false;
	for (int loop = 0; !died && loop < 5 /*For example */; ++loop)
	{
		int status;
		sleep(1);
		if (waitpid(_pid, &status, WNOHANG) == _pid) died = true;
	}

	if (!died) kill(_pid, SIGKILL);
}

bool  Utils::checkProcess( void ) {
  if (!access(".checker", F_OK))
    return true;
  else
    open(".checker", O_CREAT);
  return false;
}
