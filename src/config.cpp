/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/29 19:10:50 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/config.hpp"

Config::Config(void) {
  std::cout << "" << std::endl;

  
}

Config::Config(std::string _filename): filename(_filename) { }

Config::~Config(void){ std::cout << "" << std::endl; }
     
void  Config::parseConfig(void) {
  std::ifstream file(filename.data());
  std::string   buffer;
  
  if (!file.is_open())
    std::logic_error("file no open");

  while (getline(file, buffer, '\n')) {
      
      std::cout << buffer << std::endl;
    
    }
}
