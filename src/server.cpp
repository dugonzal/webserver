/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/03 23:40:37 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server.hpp"

Server::Server(void) { 

  std::cout << "" << std::endl; 
  
}

Server::Server(const std::string &_host, int _port): host(_host), port(_port) { }

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


  // AF_INET6 -> IPv6 no referimo a la familia de protocolos disponibles
  addr.sin_family = AF_INET6;
 
  // htons -> host to network short (16 bits) cambiamos a bytes
  addr.sin_port = htons(8080);
  
  std::cout << "addr.sin_family: " << addr.sin_family << std::endl;
}
