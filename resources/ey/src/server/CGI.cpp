/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/26 10:10:20 by Dugonzal         ###   ########.fr       */
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

const string  CGI::handlerCgi(void) {
  int pid;

  logger.Log("intenta ejecutar el descriptor de archivo");
  pid = fork();
  if (pid < 0) {
    logger.Log("fork error");
    return ("error");
  }
  if (!pid) {
    const char *tmp[3];

    tmp[0] = path.data();
    tmp[1] = fileName.data();
    tmp[2] = NULL;
    if (execve(*tmp, (char *const *)(tmp), NULL) < 0) {
        logger.Log("error cgi");
    }
    exit(0);
  } else {
    int tmp;
    waitpid(pid, &tmp, 0);
  }
  return(result.append("CGI OK"));
}

void CGI::clear(void) {
}
