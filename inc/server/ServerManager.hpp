/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/23 10:09:49 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Server.hpp"
# include "../Utils.hpp"

class ServerManager {
 private:
  size_t                    nServers;
  std::deque<int>           portsServers;
  vector<string>            hostServers;
  vector<string>            nameServers;
  map<int, string>          errorPage;
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
  void  setServers(size_t _amount);
  void  startServers(void);
  void  setSelect(void);

  int   setPort(int _nServer, const string& _host, int _port);
  int   setName(const string& _name);
  int   setErrorPage(const string& _errorPages);
  int   setClientBodySize( const string& _clientBodySize);
};
