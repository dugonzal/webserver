/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/14 20:18:01 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Server.hpp"
# include "../Utils.hpp"

class ServerManager {
 private:
  size_t                          nServers;
  Server                          server;
  vector<Server>                  vServers;
  struct                          timeval timeout;
  fd_set                          cSockets, rSockets, wSockets;
  mutable map<string, Location>   *location;
 public:
  ServerManager(void);
  ~ServerManager(void);
  ServerManager(const ServerManager&);
  ServerManager &operator=(const ServerManager&);

 public:
  void  setNServers(size_t);
  void  startServers(void);
  void  setSelect(void);
  void  addServer(Server);
  int   setServerName(const string&);
  void  setLocations(map<string, Location>*);
};
