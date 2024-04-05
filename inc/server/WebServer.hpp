/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/04 21:59:35 by Dugonzal         ###   ########.fr       */
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
  mutable ServerManager servers;
  mutable Parser        parser;
  mutable Signals       signals;
  mutable size_t        nServers;
  map<string, Location> locations;

 private:
  WebServer(void);

 private:
  void  setServerWebServer(void);
  void  printServer(const vector<string>&, size_t);
  void  setLocation(const vector<string>&, size_t); 

 public:
  explicit WebServer(const string&);
  WebServer(const WebServer&);
  WebServer &operator=(const WebServer&);
  ~WebServer(void);
  void  setServer(void);
};
