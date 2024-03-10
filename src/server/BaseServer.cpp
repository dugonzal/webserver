/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:29:03 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/10 21:25:20 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/BaseServer.hpp"

BaseServer::BaseServer(void): addrLen(sizeof(addr)), s(-42), opt(1), port(-1)  {
  ::bzero(&addr, sizeof(addr));
  memset(clientMsg, 0, sizeof(clientMsg));
}

BaseServer::BaseServer(const BaseServer &copy): \
  addrLen(copy.addrLen), s(copy.s), opt(copy.opt) { }

BaseServer &BaseServer::operator=(const BaseServer &copy) {
  if (this != &copy) {
    addr = copy.addr;
    addrLen = copy.addrLen;
    s = copy.s;
    data = copy.data;
    opt = copy.opt;
    wConnections = copy.wConnections;
    error_page = copy.error_page;
    buffer = copy.buffer;
    if (options && copy.options) // Only if the two have data inside
        *options = *(copy.options);
    else // Depending on copy.options, NULL or copy.options.
        options = copy.options ? new int(*copy.options) : nullptr;
  }
  return (*this);
}

BaseServer::~BaseServer(void) { ::close(s); }

int BaseServer::createSocket(void) {
  if ((this->s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     throw std::logic_error("socket creation failed");

  assert((s > 2) && (s < 6553));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(this->port);
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");

  if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
    &opt, sizeof(opt)) < 0)
      throw std::logic_error(strerror(errno));

  if (bind(s, (sockaddr *)&addr, addrLen) <  0)
    throw std::logic_error(strerror(errno));

  if (listen(s, this->wConnections) < 0)
    throw std::logic_error("listen failed");
  
  int sN; // client file descriptor
  if ((sN = accept(this->s, (sockaddr *)&clientAddr, &addrClientLen)) < 0)
    throw std::logic_error("accept failed");
  struct timeval timeout;
  timeout.tv_sec = 3; // 10 segundos
  timeout.tv_usec = 0;

  if (setsockopt(sN, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
      std::cerr << "Error al establecer el tiempo de espera para la recepción de datos" << std::endl;
      return -1;
  }
  int ret = recv(sN, clientMsg, sizeof(clientMsg) - 1, 0);
  if (ret == 0 || ret == -1) {
    close(s);
    close(sN);
    throw std::logic_error("recv failed");
  }

  //  en la resta del cliente entraria la parte de la peticion o request del cliente
  // read(sN, &buffer, 1023);

  // en la respuesta del cliente entraria la parte de la respuesta del servidor
  std::string response = "HTTP/1.1 200  OK\r\n\r\n <html><head></head><body><h1 text-family=\"Roboto\" align=\"center\"> Hello, Inception42! </h1></body></html>";
    //Content-Length: 13\r\nContent-Type: text/plain\r\n\r\nHello, World!";
  send(sN, response.data(), response.size(), 0);
  
  close(sN); // Second, client fd is closed
  close(s);

  std::cout << clientMsg << std::endl;
  // memset(clientMsg, 0, sizeof(clientMsg));
  return (s);
}



int   BaseServer::getSocket(void) const { return (s); }

bool   BaseServer::checkServer( void ) const {
  if (this->port <= 0 || this->server_name.empty())
    return false;
  return true;
}

void BaseServer::setServer(void) {}

void BaseServer::setWConnections( int _amount ) {
  this->wConnections = _amount;
}

void BaseServer::setPort( int _port ) {
  this->port = _port;
}

void  BaseServer::setServerName( const std::string& _sName ) {
  this->server_name = _sName;
}

std::ostream &operator<<(std::ostream &os, const BaseServer &copy) {
  os << "host: " << copy.getSocket() << std::endl;
  return (os);
}
