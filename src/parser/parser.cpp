/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/20 20:02:01 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/parser.hpp"

Parser::Parser(void) {}

Parser::~Parser(void) {}

Parser::Parser(const std::string &_filename): filename(_filename) {
  
  std::ifstream   file(filename.data());
  std::string     buffer;

  assert(file.is_open() == true);
  if (file.bad() || file.fail() || file.eof())
    throw std::logic_error("file no open");

  while (getline(file, buffer, '\n')) {
    buffer = trim(buffer); // clean line
    if (buffer.empty() || buffer[0] == '#')
       continue;
    else if (buffer.find("include") != std::string::npos)
      readIncludeError(buffer.substr(buffer.find_first_of(" ") + 1));
    else
      data.push_back(buffer);
  }
  
  file.close();
  getData();
  assert(file.is_open() == false);
}
    
void  Parser::getData(void) {
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
      buffer = trim(buffer);
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
