/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/29 17:44:39 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server.hpp"
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>

Server::Server(void) { 

  std::cout << "" << std::endl; 
  
}

Server::~Server(void) { std::cout << "" << std::endl; }

/*
 * el socket tiene 2 argumentos
 * 0 -> familia selecciona el tipo de comunicacion en este caso es, AF_INET or AF_INET6
 * * */
void Server::setServer(void) {
//  struct sockaddr_in addr;
  //socket(int domain, int type, int protocol)
  if ((this->s = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) < 0)
     throw std::logic_error("Error: socket creation failed");
  
  std::cout << this->s << std::endl;
  // seteo la estructura addr a 0
  memset(&this->addr, 0, sizeof(addr));

  
  addr.sin_family = AF_INET6;
  addr.sin_port = htons(8080);
  
  std::cout << "addr.sin_family: " << addr.sin_family << std::endl;
}
