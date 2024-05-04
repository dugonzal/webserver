/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/04 12:28:47 by jaizpuru         ###   ########.fr       */
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

void  CGI::readFd(int fd) {
  std::string buffer;
  std::ifstream readFile("cgi.out");
  
  while (getline(readFile, buffer, '\n')) {
    result.push_back(buffer);
  }

  close(fd);
}

const vector<string>& CGI::getCgi(void) const { return result; }

void  CGI::handlerCgi(void) {
  result.clear();
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
        logger.Log("error cgi");
    }
    logger.Log("error cgi -42");
    exit(-42);
  }
  if (waitpid(pid, &tmp, 0) < 0) {
    return logger.Log("error waitpid cgi");
  }
  close(out);
  close(err);
  out = open("cgi.out", O_RDONLY);
  if (out < 0)
      return (logger.Log("error: CGI: could not open file for reading"));
  if (tmp > -1) {
    readFd(out);
  } else {
    readFd(err);
  }
  remove("cgi.out");
  remove("cgi.err");
  for (size_t it = 0; it < result.size(); it++)
    std::cout << result[it] << std::endl;
}

void CGI::clear(void) {
  file.clear();
  root.clear();
  result.clear();
}
