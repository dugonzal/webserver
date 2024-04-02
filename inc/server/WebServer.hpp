/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/02 20:50:19 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/Parser.hpp"
# include "../Signals.hpp"
# include "Server.hpp"
# include "../Utils.hpp"
# include "../server/ServerManager.hpp"

/*
 * voy a usar el vector de servidores para obtener la data puedo crear una pequeña funcoion que parsee y comprueba 
 * la informcaion dentro del scope del servidor, cada server tendra un vector de string buffer 
 * que recibira el scope del buffer una vez que el scope este parceado
 * */
class WebServer {
 private:
  ServerManager servers;
  Parser        parser;
  Signals       signals;
  size_t        nServers;
 private:
  WebServer(void);

 private:
  void  setServerWebServer( void );

 public:
  explicit WebServer(const string&);
  WebServer(const WebServer&);
  WebServer &operator=(const WebServer&);
  ~WebServer(void);
  void  setServer(void);
};
