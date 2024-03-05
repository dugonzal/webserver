/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:41 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/05 12:09:19 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/VirtualServer.hpp"

VirtualServer::VirtualServer(void) { }

VirtualServer::~VirtualServer(void) { }

VirtualServer::VirtualServer(const VirtualServer &copy): \
  vServers(copy.vServers) { }

VirtualServer &VirtualServer::operator=(const VirtualServer &copy) {
  if (this != &copy)
    vServers = copy.vServers;

  return (*this);
}

void  VirtualServer::addServer(Server server) {
  vServers.push_back(server.clone());
}
