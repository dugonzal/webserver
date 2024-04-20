/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:04:49 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/20 16:39:23 by Dugonzal         ###   ########.fr       */
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
