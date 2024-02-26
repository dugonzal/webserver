/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/26 21:39:07 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Config.hpp"

Config::Config(void) { }

Config::~Config(void) { }

Config::Config(const string &filename) {
  parser = Parser(filename);
  setServers();
}


void  Config::setServers(void) {
 // std::vector<string> tmp = );

  parser.printData(parser.getData());
}
