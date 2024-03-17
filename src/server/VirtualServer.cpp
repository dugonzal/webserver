/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 20:50:58 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/VirtualServer.hpp"

VirtualServer::VirtualServer(void) { }

VirtualServer::VirtualServer(const Parser &parser) {
  vector<string> **tmp = parser.getDataServers();

  for (int i = 0; i < parser.getNservers(); i++) {
    if (tmp[i]->empty()) {
        delete tmp[i];
        continue;
    }
    addServer((Server(*tmp[i])));
    delete tmp[i];
  }
  delete [] tmp;
}

VirtualServer::~VirtualServer(void) {
  for (unsigned int i = 0; i < vServers.size(); i++)
    delete vServers[i];
  vServers.clear();
}

VirtualServer::VirtualServer(const VirtualServer &copy): \
  vServers(copy.vServers) { }

VirtualServer &VirtualServer::operator=(const VirtualServer &copy) {
  if (this != &copy)
    parser = copy.parser;

  return (*this);
}

void  VirtualServer::addServer(Server server) {
  vServers.push_back(server.clone());
}
