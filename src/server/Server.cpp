/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal Dugonzal@student.42urduliz.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:04:49 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/06/18 17:25:13 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Server.hpp"

Server::Server(void): BaseServer() { }

Server::~Server(void) { }

Server::Server(const Server &copy): BaseServer(copy) { }

Server &Server::operator=(const Server &copy) {
  if (this not_eq &copy) {
    BaseServer::operator=(copy);
    request = copy.request;
  }
  return (*this);
}

void  Server::setLocationRequest(void) {
  request.setHostAndPort(host, port);
  request.setLocation(location);
}

void  Server::handlerClient(size_t fd, const char *header) {
  request.serverToClient(header, fd);
}
