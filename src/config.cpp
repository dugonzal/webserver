/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/29 23:53:34 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/config.hpp"
# include "../inc/server.hpp"

Config::Config(void) {
  std::cout << "" << std::endl;

  
}

Config::Config(std::string _filename): filename(_filename) { }

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
