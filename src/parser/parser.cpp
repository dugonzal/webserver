/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/20 18:53:21 by Dugonzal         ###   ########.fr       */
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

// tengo que almacenar los includes terminal de leer y luego leerlos abajo para empezar a paresear
Parser::Parser(const std::string &_filename): filename(_filename) {
  
  std::ifstream   file(filename.data());
  std::string     buffer;

  assert(file.is_open() == true);
  if (file.bad() || file.fail() || file.eof())
    throw std::logic_error("file no open");

  while (getline(file, buffer, '\n')) {
    if (buffer.empty() || buffer[0] == '#')
        continue;
    data.push_back(buffer);
  }
  
  file.close();
  getInclude();
  assert(file.is_open() == false);
}
    
void  Parser::getInclude(void) {
  for (unsigned int i = 0; i < data.size(); i++ ) {
    std::cout << data[i] << std::endl;
    if (data[i].find("include") != std::string::npos)
      readIncludeError(data[i].substr(data[i].find_last_of(" ") + 1));
  }
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
    file.close();
}
   
void Parser::readIncludeError(std::string fileName) {
 
  if (fileName[fileName.size() - 1] == ';')
    fileName[fileName.size() - 1] = '\0';
  else
    throw std::runtime_error("no termine en  \";\"");
  readInclude(fileName);
}
