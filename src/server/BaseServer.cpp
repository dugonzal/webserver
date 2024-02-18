/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/18 20:25:23 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>

BaseServer::BaseServer(void) {
  // seteo la estructura addr a 0
  memset(&this->addr, 0, sizeof(addr));
}

BaseServer::BaseServer(const std::string &_host, int _port): \
  host(_host), port(_port) {}

BaseServer::~BaseServer(void) { close(s); }

int BaseServer::setSocket(void) {
  addrLen = sizeof(addr);
  opt = 1;

  if ((this->s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     throw std::logic_error("socket creation failed");
  assert((s > 2) && (s < 6553));
  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8000);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt)) < 0)
      throw std::logic_error (strerror(errno)); 
  if (bind(s, (struct sockaddr *)&addr, addrLen) <  0)
    throw std::logic_error (strerror(errno)); 

/*  if (listen(this->s, this->s) < 0)
    throw std::logic_error("listen failed");
  int sN;
  if ((sN = accept(this->s, (struct sockaddr *)&addr, &addrLen)) < 0)
    throw std::logic_error("accept failed");
     struct timeval timeout;
  timeout.tv_sec = 3; // 10 segundos
  timeout.tv_usec = 0;
  if (setsockopt(sN, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
      std::cerr << "Error al establecer el tiempo de espera para la recepción de datos" << std::endl;
      return -1;
  }
  std::cout << "Connection accepted" << std::endl;
  if (recv(sN, buffer, 1023, 0) < 0)
    throw std::logic_error("recv failed");
  //  en la resta del cliente entraria la parte de la peticion o request del cliente
  read(sN, buffer, 1023);
  std::cout << buffer << std::endl;

  // en la respuesta del cliente entraria la parte de la respuesta del servidor
  std::string response = "HTTP/1.1 200  OK\r\n\r\n <h1 align=\"center\"> Hello, World! </h1>";
    //Content-Length: 13\r\nContent-Type: text/plain\r\n\r\nHello, World!";
  send(sN, response.data(), response.size(), 0);
  close(sN);
  */
  return (s);
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
