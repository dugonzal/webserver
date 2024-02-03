/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/03 23:50:44 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parser.hpp"
    
Parser::Parser(const std::string &_filename): filename(_filename) {}

Parser::Parser(void) {}

Parser::~Parser(void) {}
    
void  Parser::parser(void) {
  
  std::ifstream   file(filename.data());
  std::string     buffer;

  if (!file.is_open() || file.bad())
    throw std::logic_error("Error: file no open");

  // avanzo hasta el primer server del archivo de configuracion
  while (getline(file, buffer, '\n'))
    if (buffer.find("server") !=  std::string::npos \
        && buffer.find("{") !=  std::string::npos)
      break;  
   
  std::cout << "pasado el while" << std::endl;

  if (buffer.find("server") ==  std::string::npos \
      || buffer.find("{") ==  std::string::npos)
    throw std::logic_error("Error: no server found");
  std::cout << "pasado el while" << std::endl;

  data.push_back(buffer);
  while (getline(file, buffer, '\n')) {
    data.push_back(buffer);
  }
  file.close();
}
