/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:04:49 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/03 09:24:14 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Server.hpp"

Server::Server(void) {
  std::cout << "" << std::endl;
}

Server::~Server(void) {
  std::cout << "" << std::endl;
}


BaseServer *Server::clone(void) const {
  return (new Server(*this));
}
