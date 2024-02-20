/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:48 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/20 13:00:59 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/parser.hpp"
#include <cstddef>
#include <iterator>
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
        std::cout << buffer << std::endl;
        std::string cadena("include \t\r\n;");
      // voy a tirar por un enfoque de iterar la cadena pero buscare una forma mas efectiva de hacerlo la libreria estandar
        for (long unsigned int i = 0; i < cadena.size(); i++) {
            std::cout << cadena[i] << std::endl;
            while (std::size_t pos = buffer.find(cadena[i]) != std::string::npos)
            {
                std::cout << pos <<  "   " << (buffer.find(cadena[i]) != std::string::npos) << std::endl;
            }
        }
        std::cout << buffer << std::endl;
        exit(0);
    }
    else if (buffer[buffer.size()] == ';')
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

// voy a parsear la data para buscar los errores
int  Parser::getParser(void)  {
  std::vector<std::string>::iterator  it = data.begin();
  while (it != data.end())  {
    if  (((*it).find("server") != std::string::npos \
      && (*it).find("{")  != std::string::npos))
        NS++;
    std::cout << *it++ << std::endl;
  }
//  std::cout << "NS: " << NS << std::endl;
  return (NS);
}
