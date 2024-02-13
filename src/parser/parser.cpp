/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/13 01:23:20 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/parser.hpp"
# include <cassert>
#include <string>

Parser::Parser(void) {}

Parser::~Parser(void) {}
    
Parser::Parser(const std::string &_filename): filename(_filename) {
  
  std::ifstream   file(filename.data());
  std::string     buffer;

  std::cout << "filename: ->:" << filename << std::endl;
  if (file.bad() || file.fail() || file.eof())
    throw std::logic_error("file no open");

  // avanzo hasta el primer server del archivo de configuracion
  while (getline(file, buffer, '\n'))
    if (buffer.find("server") !=  std::string::npos \
      && buffer.find_first_of("{") != std::string::npos)
        break;  

  std::cout << "buffer: ->:" << buffer << std::endl;

  data.push_back(buffer);
  while (getline(file, buffer, '\n'))
    data.push_back(buffer);

  file.close();
//  assert(file.is_open() == false);
//  handlerError();
}

int Parser::getNS(void) {
 
  NS = 0;
  return NS;
}

// voy a parsear la data para buscar los errores
void  Parser::handlerError(void) {

  std::vector<std::string>::iterator  it = data.begin(); 

  while (it != data.end()) 
    std::cout << *it++ << std::endl;
}
