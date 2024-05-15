/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/15 19:42:15 by jaizpuru         ###   ########.fr       */
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
	int retCode;
	int pid, sleepPid;

	int err = open("cgi.err", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	int out = open("cgi.out", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	result.clear();
	if (err < 0 || out < 0) {
		return(logger.Log("error open file cgi"));
	}

	sleepPid = fork();
	if (sleepPid < 0)
		return(logger.Log("error fork"));
	if (!sleepPid) {
		sleep(4);
		exit(-42);
	}

	pid = fork();
	if (pid < 0) {
		killProcess(sleepPid);
		return(logger.Log("error fork"));
	}
	if (!pid) {
		const char *tmp[3] = { path.data(), fileName.data(), NULL };

		if (dup2(out, STDOUT_FILENO) < 0 || dup2(out, STDERR_FILENO) < 0)
			exit(EXIT_FAILURE);
		if (execve(*tmp, (char *const *)(tmp), NULL) == -1) {
			logger.Log("error cgi -42");
		}
		exit(-42);
	}
	if (waitpid(0, &retCode, 0) == sleepPid) {
		killProcess(pid);
		close(out);
		close(err);
		readFd("cgi.out");
		remove("cgi.err");
		result.push_back("<h1>error: CGI: timeout</h1>");
		return logger.Log("error waitpid cgi");
	}
	killProcess(sleepPid);
	close(out);
	close(err);
	int ret = WEXITSTATUS(retCode);
	if (WIFEXITED(retCode) && ret > -1) {
		err = open("cgi.out", O_RDONLY);
		readFd("cgi.out");
		close(out);
		remove("cgi.err");
		remove("cgi.out");
	} else {
		err = open("cgi.err", O_RDONLY);
		readFd("cgi.err");
		remove("cgi.out");
		close(err);
		remove("cgi.err");
	}
}

void CGI::clear(void) {
  file.clear();
  root.clear();
  result.clear();
}
