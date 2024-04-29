/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/29 15:31:44 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/CGI.hpp"

CGI::CGI(void) { }

CGI::~CGI(void) { }

CGI::CGI(const CGI &copy): result(copy.result) { }

CGI &CGI::operator=(const CGI &copy) {
  if (this != &copy) {
    result = copy.result;
  }
  return(*this);
}

void  CGI::setCgi(const string &_path, const string &_fileName) {
  path = (char *)_path.data();
  fileName = (char*)_fileName.data();
  cout << path  << "  " << fileName << endl;
}

std::string CGI::getCgi( void ) const {
  return result;
}

const string  CGI::handlerCgi(void) {
  result.clear();
  int pid;
  char buffer[128];
  int fdFile = open("cgi.out", O_CREAT | O_RDWR, 0666);
  if (fdFile == -1)
    throw (logic_error("error: CGI: could not open file: " + fileName));
  pid = fork();
  if (pid < 0) {
    logger.Log("fork error");
    return ("error");
  }
  if (!pid) {
    const char *tmp[3];

    dup2(STDOUT_FILENO, fdFile); /* Makes STDOUT -> fdFile */
    tmp[0] = path.data();
    tmp[1] = fileName.data();
    tmp[2] = NULL;
    if (execve(*tmp, (char *const *)(tmp), NULL) < 0) {
        logger.Log("error cgi");
    }
    close(fdFile);
    exit(0);
  } else {
    int tmp;
    waitpid(pid, &tmp, 0);
    while (read(fdFile, buffer, 128)) /* Reads the file with the content of script output */
      result.append(buffer);
  }
  remove("cgi.out"); /* Part of C++98 */
  return(result.append("CGI OK"));
}

void CGI::clear(void) {
}
