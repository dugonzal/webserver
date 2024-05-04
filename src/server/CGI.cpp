/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/04 16:07:18 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/CGI.hpp"

CGI::CGI(void) { }

CGI::~CGI(void) { }

CGI::CGI(const CGI &copy): result(copy.result), \
  path(copy.path), fileName(copy.fileName), root(copy.root) { }

CGI &CGI::operator=(const CGI &copy) {
  if (this != &copy) {
    result = copy.result;
    path = copy.path;
    fileName = copy.fileName;
    root = copy.root;
  }
  return(*this);
}

void  CGI::setCgi(const string &_path, const string &_fileName) {
  path = (char *)_path.data();
  fileName = (char*)_fileName.data();
}

void  CGI::readFd(const string &fd) {
  string buffer;
  ifstream readFile(fd.data());

  while (getline(readFile, buffer, '\n')) {
    result.push_back(buffer);
  }
  remove(fd.data());
}

const vector<string>& CGI::getCgi(void) const { return result; }

void  CGI::handlerCgi(void) {
  int tmp;
  int pid;

  int err = open("cgi.err", O_CREAT | O_TRUNC | O_WRONLY, 0666);
  int out = open("cgi.out", O_CREAT | O_TRUNC | O_WRONLY, 0666);
  if (err < 0 || out < 0) {
    return(logger.Log("error open file cgi"));
  }

  pid = fork();
  if (pid < 0)
    return(logger.Log("error fork"));
  if (!pid) {
    const char *tmp[3] = { path.data(), fileName.data(), NULL };

    if (dup2(out, STDOUT_FILENO) < 0 || dup2(out, STDERR_FILENO) < 0)
      exit(EXIT_FAILURE);
    if (execve(*tmp, (char *const *)(tmp), NULL) == -1) {
        logger.Log("error cgi -42");
    }
    exit(-42);
  }
  if (waitpid(pid, &tmp, 0) < 0) {
    return logger.Log("error waitpid cgi");
  }
  close(out);
  close(err);
  if (tmp > -1) {
    err = open("cgi.out", O_RDONLY);
    readFd("cgi.out");
    close(out);
    remove("cgi.err");
  } else {
    err = open("cgi.err", O_RDONLY);
    readFd("cgi.err");
    remove("cgi.out");
    close(err);
  }
  result.clear();
}

void CGI::clear(void) {
  file.clear();
  root.clear();
  result.clear();
}
