/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/12 12:09:12 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"

BaseServer::BaseServer(void) { 

  std::cout << "" << std::endl; 
  
}

BaseServer::BaseServer(const std::string &_host, int _port): host(_host), port(_port) { }

BaseServer::~BaseServer(void) {
  
  close (s);
}

/*
 * el socket tiene 2 argumentos
 * 0 -> familia selecciona el tipo de comunicacion en este caso es, AF_INET or AF_INET6
 * * */
void BaseServer::setServer(void) {
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
  addr.sin_addr.s_addr = INADDR_ANY; 

  // forzar la reutilizacion del socket
  if (!(setsockopt(this->s, SOL_SOCKET, SO_REUSEADDR, &this->addr, sizeof(this->addr))))
    throw std::logic_error("Error: setsockopt failed");
  //set socket options
  //int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
  // con esta funcion seteamos el socket para que pueda ser reutilizado y no de errores en las conexiones
  std::cout << "addr.sin_family: " << addr.sin_family << std::endl;

}
