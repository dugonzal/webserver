/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:04:49 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 18:47:16 by Dugonzal         ###   ########.fr       */
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
  request.setLocation(location, LocationRoot);
}

void  Server::handlerRequest(const char *header) {
  request.setHeader(header);
  request.handlerRequest();
}

void  Server::handlerResponse(size_t fd) {
  const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
  if (::send(fd, response, strlen(response), 0) < 0)
    logger.Log("error al enviar [%d]", fd);
}

void  Server::handlerClient(size_t fd, const char *header) {
  // req
  handlerRequest(header);
  /// res
  handlerResponse(fd);
}
