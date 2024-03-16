/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:49:28 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 15:07:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parser/ServerParser.hpp"

ServerParser::ServerParser(void) {}

ServerParser::~ServerParser(void) {}

ServerParser::ServerParser(const vector<string> &tmp) {
  cout << endl << "entra al server parser de un server" << endl << endl;
  for (unsigned int i = 0; i < tmp.size(); i++)
      cout << tmp[i] << endl;
  cout << endl << "sale de un parser server" << endl << endl;
}

ServerParser &ServerParser::operator=(const ServerParser &copy) {
  if (this != &copy) {
    buffer = copy.buffer;
  }
  return (*this);
}
