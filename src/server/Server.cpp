/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:04:49 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/24 20:27:06 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Server.hpp"

Server::Server(void): BaseServer() { }

Server::~Server(void) { }

Server::Server(const Server &copy): BaseServer(copy) { }

Server &Server::operator=(const Server &copy) {
  if (this != &copy) {
    BaseServer::operator=(copy);
    request = copy.request;
  }
  return (*this);
}


void  Server::setLocationRequest(void) {
  request.setLocation(location);
}

void  Server::handlerClient(size_t fd, const char *header) {
  setLocationRequest();
  request.serverToClient(header, fd);
}
