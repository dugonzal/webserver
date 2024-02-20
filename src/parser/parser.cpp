/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/20 16:44:29 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/parser.hpp"
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

Parser::Parser(void) {}

Parser::~Parser(void) {}

Parser::Parser(const std::string &_filename): filename(_filename) {
  std::ifstream   file(filename.data());
  std::string     buffer;

  if (file.bad() || file.fail() || file.eof())
    throw std::logic_error("file no open");

  // avanzo hasta el primer server del archivo de configuracion
  while (getline(file, buffer, '\n')) {
    if (buffer.empty() || buffer[0] == '#')
        continue;
    else if (buffer.find("include") != std::string::npos) {
      // voy a tirar por un enfoque de iterar la cadena pero buscare una forma mas efectiva de hacerlo la libreria estandar
            //getRemove(buffer, "include \t\r\n;");
      readIncludeError(buffer.substr(buffer.find_last_of(" ") + 1));
       // exit(0);
    }
     data.push_back(buffer);
  }
/*
  data.push_back(buffer);
  while (getline(file, buffer, '\n'))
    data.push_back(buffer);
*/
  file.close();
  assert(file.is_open() == false);

  for (long unsigned int i = 0; i < data.size(); i++)
    std::cout << data[i] << std::endl;
}
    
void  Parser::readInclude(std::string fileName) {
    
    std::ifstream file(fileName.data());
    std::string   buffer;
    if (file.bad() || file.fail() || file.eof())
      throw std::logic_error("file no open");
 
    while (getline(file, buffer, '\n')) {
      if (buffer.empty() || buffer[0] == '#')
        continue;
      data.push_back(buffer);
    }

}
   
void Parser::readIncludeError(std::string fileName) {
 
  if (fileName[fileName.size() - 1] == ';')
    fileName[fileName.size() - 1] = '\0';
  else
    throw std::runtime_error("no termine en  \";\"");
  readInclude(fileName);
}
