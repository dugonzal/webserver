/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/02 18:31:41 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Server.hpp"
# include "../Utils.hpp"

class ServerManager {
 private:
  size_t                    nServers;
  deque<int>                portsServers;
  vector<string>            hostServers;
  vector<string>            serverName;
  vector<map<int, string> > errorPage;
  vector<int>               clientMaxBodySize;
  Server                    server;
  vector<Server>            vServers;
  map<string, Location>     locations;
  struct timeval timeout;
  fd_set cSockets, rSockets, wSockets;

 public:
  ServerManager(void);
  ~ServerManager(void);
  ServerManager(const ServerManager&);
  ServerManager &operator=(const ServerManager&);

 public:
  void  setNServers(size_t _amount);
  void  startServers(void);
  void  setSelect(void);
  void  addServer(Server _server);
  int   setServerName(const string& _name);
  int   setListenConfig(int _nServer, const string& _host, int _port);
  int   setErrorPage(const string& _errorPages);
  int   setClientBodySize( const string& _clientBodySize);
};
