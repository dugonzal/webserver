/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/16 15:14:27 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h>

BaseServer::BaseServer(void) {
  // seteo la estructura addr a 0
  memset(&this->addr, 0, sizeof(addr));
}

BaseServer::BaseServer(const std::string &_host, int _port): \
  host(_host), port(_port) {}

BaseServer::~BaseServer(void) { close(s); }

int BaseServer::setBind(void) {
  addrLen = sizeof(addr);
  opt = 1;
  if ((this->s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     throw std::logic_error("socket creation failed");
  assert((s > 2) && (s < 6553));
  // AF_INET6 -> IPv6 no referimo a la familia de protocolos disponibles
  addr.sin_family = AF_INET;
  // htons -> host to network short (16 bits) cambiamos a bytes
  addr.sin_port = htons(8000);
  //addr.sin_port = htons(port);
  std::cout << s << std::endl;
  std::string ip = "127.0.0.1";
  addr.sin_addr.s_addr = inet_addr(ip.data());
//    inet_addr(ip.c_str());
    //gethostname((char *)(ip.data()), 100);
  // forzar la reutilizacion del socket
  if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    throw std::logic_error("setsockopt failed");
  if (bind(s, (struct sockaddr *)&addr, addrLen) < 0)
    throw std::logic_error("bind failed");
  if (listen(this->s, this->s) < 0)
    throw std::logic_error("listen failed");
  int sN;
  if ((sN = accept(this->s, (struct sockaddr *)&addr, &addrLen)) < 0)
    throw std::logic_error("accept failed");
  std::cout << sN << std::endl;
  char buffer[1024] = { 0 };
  read(sN, buffer, 1023);
  std::cout << buffer << std::endl;
  std::string response = "HTTP/1.1 200  OK\r\n\r\n <h1 align=\"center\"> Hello, World! </h1>";
    //Content-Length: 13\r\nContent-Type: text/plain\r\n\r\nHello, World!";
  send(sN, response.data(), response.size(), 0);
  close (sN);
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
