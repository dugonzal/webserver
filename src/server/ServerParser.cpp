/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:38:10 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/19 09:38:49 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/ServerParser.hpp"

ServerParser::ServerParser(void) {}

ServerParser::~ServerParser(void) {cout << "salgo de ServerParser" << endl;}

ServerParser::ServerParser(const vector<string> &tmp): buffer(tmp) {
  cout << "entro a ServerParser" << endl;
  /*cout << endl << "entra al server parser de un server" << endl << endl;
  for (unsigned int i = 0; i < tmp.size(); i++)
      cout << tmp[i] << endl;
  cout << endl << "sale de un parser server" << endl << endl;
*/}

ServerParser &ServerParser::operator=(const ServerParser &copy) {
  if (this != &copy) {
    buffer = copy.buffer;
  }
  return (*this);
}
