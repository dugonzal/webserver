/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/30 15:46:34 by jaizpuru         ###   ########.fr       */
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
  int fdFile = open("cgi.out", O_CREAT | O_TRUNC | O_WRONLY, 0666);
  if (fdFile == -1)
    throw (logic_error("error: CGI: could not open file: " + fileName));
  pid = fork();
  if (pid < 0) {
    logger.Log("fork error");
    return ("error");
  }
  if (!pid) {
    const char *tmp[3];

    tmp[0] = path.c_str();
    tmp[1] = fileName.c_str();
    tmp[2] = NULL;
    if (dup2(fdFile, STDOUT_FILENO) == -1) /* Makes fdFile -> STDOUT */
      exit (EXIT_FAILURE);
    if (execve(*tmp, (char *const *)(tmp), NULL) < 0) {
        logger.Log("error cgi");
    }
    exit(0);
  } else {
    int tmp;
    waitpid(pid, &tmp, 0);
    std::cout << "execve return code : " << tmp << std::endl;
    if (tmp == EXIT_FAILURE)
      logger.Log("error: CGI: dup2() failed");
  }
  close(fdFile); /* Close file used to write */
  fdFile = open("cgi.out", O_RDONLY);
  if (fdFile == -1) {
      logger.Log("error: CGI: could not open file for reading");
      return ("error");
  }
  int bytesRead;
  while ( (bytesRead = read(fdFile, buffer, sizeof(buffer))) > 0) /* Reads the file with the content of script output */ {
    buffer[bytesRead] = '\0';
    result.append(buffer); }
  close(fdFile);
  remove("cgi.out"); /* Part of C++98 */
  return(result);
}

void CGI::clear(void) {
}
