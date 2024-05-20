/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/20 15:52:30 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Signals.hpp"
# include "../Logger.hpp"
# include "Server.hpp"
# include "../Utils.hpp"

class ServerManager: private virtual Utils {
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
  void  startServers(void);
  void  setNServers(size_t);
  void  setLocations(map<string, Location>*);

 private:
  void  handlerPoll(void);
  void  initPoll(void);
  void  addClient(void);
  bool  removeDuplicateServers(const string&, int port);
  bool  selectServerForClient(size_t, size_t);
};
