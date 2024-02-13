/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/13 01:33:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"
#include <cassert>

BaseServer::BaseServer(void) { 
  
  // seteo la estructura addr a 0
  memset(&this->addr, 0, sizeof(addr));
  
  if ((this->s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
     throw std::logic_error("Error: socket creation failed");
 
  assert((s > 2) && (s < 6553));
}

BaseServer::BaseServer(const std::string &_host, int _port): host(_host), port(_port) { }

BaseServer::~BaseServer(void) {
  
  close (s);
}

int BaseServer::setBind(void) {
  
  // AF_INET6 -> IPv6 no referimo a la familia de protocolos disponibles
  addr.sin_family = AF_INET;
  // htons -> host to network short (16 bits) cambiamos a bytes
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY; 

  // forzar la reutilizacion del socket
  if ((setsockopt(this->s, SOL_SOCKET, SO_REUSEADDR, &this->addr, sizeof(this->addr)) < 0 ))
    throw std::logic_error("Error: setsockopt failed");
  
  if (bind(this->s, (struct sockaddr *)&this->addr, sizeof(this->addr)) < 0)
    throw std::logic_error("Error: bind failed");
  return (true);
}

int   BaseServer::getSocket(void) const { return (s); }
/*
 * el socket tiene 2 argumentos
 * 0 -> familia selecciona el tipo de comunicacion en este caso es, AF_INET or AF_INET6
 * * */
void BaseServer::setServer(void) {
}
    

std::ostream &operator<<(std::ostream &os, const BaseServer &copy) {
  os << "host: " << copy.getSocket() << std::endl;
  return (os);
}
    
