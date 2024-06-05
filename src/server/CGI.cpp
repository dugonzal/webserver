/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/06/02 21:17:55 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/CGI.hpp"

CGI::CGI(void) { }

CGI::~CGI(void) { }

CGI::CGI(const CGI &copy): result(copy.result), \
  path(copy.path), fileName(copy.fileName), root(copy.root) { }

CGI &CGI::operator=(const CGI &copy) {
  if (this not_eq &copy) {
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

void	CGI::setQuery( string& _query ) {
	query = _query;
}

const string& CGI::getCgi(void) const { return result; }

void  CGI::handlerCgi( void ) {
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
    	extern char **environ;
		const char *tmp[3] = { path.data(), fileName.data(), NULL };

		if (dup2(out, STDOUT_FILENO) < 0 || dup2(out, STDERR_FILENO) < 0)
			exit(EXIT_FAILURE);
		if (execve(*tmp, (char *const *)(tmp), environ) == -1) {
			logger.Log("error cgi -42");
		}
		exit(-42);
	}
  if (waitpid(0, &retCode, 0) == sleepPid) {
    	killProcess(pid);
		close(out);
		close(err);
		remove("cgi.err");
		remove("cgi.out");
		result = ("<h1>error: CGI: timeout</h1>\n");
		return logger.Log("error waitpid cgi");
	}
  	killProcess(sleepPid);
	close(out);
	close(err);
	int ret = WEXITSTATUS(retCode);
	if (WIFEXITED(retCode) && ret > -1) {
		err = open("cgi.out", O_RDONLY);
    	result = (readFile("cgi.out"));
		close(out);
		remove("cgi.err");
		remove("cgi.out");
	} else {
		err = open("cgi.err", O_RDONLY);
    	result = (readFile("cgi.err"));
		close(err);
		remove("cgi.out");
		remove("cgi.err");
	}
}

void CGI::clear(void) {
  file.clear();
  root.clear();
  result.clear();
}
