/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/22 08:56:55 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Server.hpp"
# include "../Utils.hpp"

class ServerManager {
 private:
  size_t                         nServers;
  std::deque<int>          portsServers;
  std::vector<string>                 hostServers;
  std::vector<string>            nameServers;
  std::map<int, string>          errorPage;
  std::vector<int>               clientMaxBodySize;
  Server                 server;
  std::vector<Server>  vServers;

  struct timeval timeout;
  fd_set cSockets, rSockets, wSockets;

 public:
  ServerManager(void);
  ~ServerManager(void);
  ServerManager(const ServerManager&);
  ServerManager &operator=(const ServerManager&);
 public:
  void  setServers( size_t _amount );
  void  startServers( void );
  void  setSelect( void );

  int   setPort( int _nServer, const std::string& _host, int _port );
  int   setName( const std::string& _name );
  int   setErrorPage( const std::string& _errorPages );
  int   setClientBodySize( const std::string& _clientBodySize );
};
