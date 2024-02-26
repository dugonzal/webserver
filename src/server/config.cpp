/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/26 19:56:29 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/config.hpp"

Config::Config(void) {
//  std::cout << "" << std::endl;
}

Config::Config(const string &filename) {
  parser = Parser(filename);
  setServers();
}

Config::~Config(void) {
//  std::cout << "" << std::endl;
}

void  Config::setServers(void) {
 // std::vector<string> tmp = );

  parser.printData(parser.getData());
}
