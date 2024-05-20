/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:04:49 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/20 11:55:02 by jaizpuru         ###   ########.fr       */
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
  request.setHostAndPort(host, port);
  request.setLocation(location);
}

void  Server::setEnviroment( char** _environ ) {
  request.setEnviroment(_environ);
}

void  Server::handlerClient(size_t fd, const char *header) {
  request.serverToClient(header, fd);
}
