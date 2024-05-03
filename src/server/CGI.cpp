/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/03 18:57:44 by Dugonzal         ###   ########.fr       */
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
  int tmp;
  int pid;
  char buffer[128];

  int err = open("cgi.err", O_CREAT | O_TRUNC | O_WRONLY, 0666);
  int out = open("cgi.out", O_CREAT | O_TRUNC | O_WRONLY, 0666);
  if (err < 0 || out < 0)
    throw (logic_error("error: CGI: could not open file: "));
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
    if (dup2(out, STDOUT_FILENO) == -1 || dup2(out, STDERR_FILENO) == -1)
      exit(EXIT_FAILURE);
    if (execve(*tmp, (char *const *)(tmp), NULL) < 0) {
        logger.Log("error cgi");
    }
    exit(-42);
  } else {
    waitpid(pid, &tmp, 0);
    std::cout << "execve return code : " << tmp << std::endl;
    if (tmp == EXIT_FAILURE)
      logger.Log("error: CGI: dup2() failed");
  }
  close(out); /* Close file used to write */
  out = open("cgi.out", O_RDONLY);
  if (out < 0) {
      logger.Log("error: CGI: could not open file for reading");
      return ("error");
  }
  int bytesRead;
  if (tmp > 0) {
    while ((bytesRead = read(out, buffer, sizeof(buffer))) > 0) /* Reads the file with the content of script output */ {
      buffer[bytesRead] = '\0';
      result.append(buffer); }
    close(out);
    close(err);
    remove("cgi.out"); /* Part of C++98 */
    remove("err.out"); /* Part of C++98 */
  } else {
    while ((bytesRead = read(err, buffer, sizeof(buffer))) > 0) /* Reads the file with the content of script output */ {
      buffer[bytesRead] = '\0';
      result.append(buffer); }
    close(out);
    close(err);
    remove("cgi.out");
    remove("err.out");
  }
  return(result);
}

void CGI::clear(void) {
}
