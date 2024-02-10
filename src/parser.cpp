/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/08 12:47:38 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parser.hpp"
#include <string>

Parser::Parser(void) {}

Parser::~Parser(void) {}
    
Parser::Parser(const std::string &_filename): filename(_filename) {
  
  std::ifstream   file(filename.data());
  std::string     buffer;

  if (file.bad() || file.fail() || file.eof())
    throw std::logic_error("file no open");

  // avanzo hasta el primer server del archivo de configuracion
  while (getline(file, buffer, '\n'))
    if (buffer.find("server") !=  std::string::npos \
      && buffer.find_first_of("{") != std::string::npos)
      break;  

  data.push_back(buffer);
  while (getline(file, buffer, '\n'))
    data.push_back(buffer);

  file.close();
  
  parser();
}

// voy a parsear la data para buscar los errores
void  Parser::handlerError(void) {

  std::vector<std::string>::iterator  it = data.begin(); 

  while (it != data.end()) {
    if (it->find("server") != std::string::npos \
      && it->find_first_of("{") != std::string::npos) {
        serverError(it); 
        continue;
    }
    it++;
  }
}
    
std::vector<std::string>::iterator  &Parser::serverError(std::vector<std::string>::iterator &it) {

  std::vector<std::string> tmp;
  
  while (it != data.end()){
    if (it->find_first_of("{") != std::string::npos) {
        tmp.push_back(*it);
        it++;
      {
        while (it->find_first_of("}") == std::string::npos) {
          tmp.push_back(*it);
          if (it->find("location") != std::string::npos \
            && it->find_first_of("{") != std::string::npos) {
              continue;
          }
          it++;
        }
      }
    }
  }
  std::vector<std::string>::iterator  it2 = tmp.begin();
  while (it2 != data.end()) {
    if (it2->find("server") != std::string::npos \
      && it2->find_first_of("{") != std::string::npos) {
        break;
    }
    it2++;
  }
  return (it);
}
    
void  Parser::parser(void) {
  // llamo a la funcion que va controlar los casos de error 
  handlerError(); 
}
