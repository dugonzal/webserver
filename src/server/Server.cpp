/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:04:49 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/17 12:04:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Server.hpp"

Server::Server(void) { }

Server::Server(const vector<string> &tmp): BaseServer(tmp) {
}

Server::~Server(void) { }

Server::Server(const Server &copy): BaseServer(copy) { }

Server &Server::operator=(const Server &copy) {
  if (this != &copy)
    BaseServer::operator=(copy);
  return (*this);
}

Server *Server::clone(void) const {
  return (new Server(*this));
}
