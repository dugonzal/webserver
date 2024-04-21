/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 19:23:50 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Signals.hpp"
# include "Logger.hpp"
# include "Server.hpp"
# include "../Utils.hpp"

class ServerManager {
 private:
  size_t                          nServers;
  Server                          server;
  vector<Server*>                 vServers;
  mutable map<string, Location>   *location;
  Logger                          logger;

 public:
  ServerManager(void);
  ~ServerManager(void);
  ServerManager(const ServerManager&);
  ServerManager &operator=(const ServerManager&);

 public:
  void  setNServers(size_t);
  void  startServers(void);
  int   setServerName(const string&);
  void  setLocations(map<string, Location>*);

 private:
  void  handlerPoll(void);
  void  addServer(Server);
  void  initPoll(void);
  void  addClient(void);
  bool  removeDuplicateServers(const string&, int port);
  bool  selectServerForClient(size_t);
};
