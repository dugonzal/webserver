/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/30 00:58:50 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/config.hpp"
# include "../inc/server.hpp"
#include <istream>
#include <string>
#include <vector>

Config::Config(void) {
  std::cout << "" << std::endl;

  
}

Config::Config(std::string _filename): filename(_filename) {

  std::ifstream   file(filename.data());
  std::string     buffer;

  if (!file.is_open() || file.bad())
    throw std::logic_error("Error: file no open");

  // avanzo hasta el primer server del archivo de configuracion
  while (getline(file, buffer, '\n'))
    if (buffer.find("server") !=  std::string::npos \
        && buffer.find("{") !=  std::string::npos)
      break;  
    
  if (buffer.find("server") ==  std::string::npos \
      || buffer.find("{") ==  std::string::npos)
    throw std::logic_error("Error: no server found");

  data.push_back(buffer);
  while (getline(file, buffer, '\n'))
    data.push_back(buffer);

  file.close();
  for (std::vector<std::string>::const_iterator it = data.begin(); it != data.end(); ++it)
    std::cout << *it << std::endl;

}

Config::~Config(void){ std::cout << "" << std::endl; }
    
/*
void  Config::parseConfig(void) {
  
  this->servers.push_back(new Server("localhost", 8080));

  std::vector<Server*>  tmp;

  tmp = this->servers;

  exit(0);
  std::ifstream file(filename.data());
  std::string   buffer;
  
  if (!file.is_open())
    std::logic_error("file no open");

  while (getline(file, buffer, '\n')) {
      
      std::cout << buffer << std::endl;
    
    }
}*/
