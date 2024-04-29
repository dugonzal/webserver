/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:44:23 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/29 10:27:59 by jaizpuru         ###   ########.fr       */
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
  return cmdOutput;
}

const string  CGI::handlerCgi(void) {
  cmdOutput.clear();
  logger.Log("intenta ejecutar el descriptor de archivo");
  std::ofstream outputFile;
  outputFile.open("cgi.out", std::ofstream::out | std::ofstream::in);
  char buffer[128];
  FILE *file = popen("/usr/bin/python3 /workspaces/webserver/resources/main.py", "r");
  if (!file) throw std::runtime_error("popen() failed!");
  while (fgets(buffer, sizeof buffer, file) != NULL) {
    cmdOutput += buffer;
  }
  return(cmdOutput);
}

void CGI::clear(void) {
}
