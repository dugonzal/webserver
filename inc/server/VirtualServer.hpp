/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/12 22:27:37 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Server.hpp"
# include "../Utils.hpp"

class VirtualServer {
 private:
  size_t                 nServers;
  int                    *portsServers;
  std::vector<string>    nameServers;
  int                    wConnections;
  Server                 server;

 public:
  VirtualServer(void);
  ~VirtualServer(void);
  VirtualServer(const VirtualServer&);
  VirtualServer &operator=(const VirtualServer&);
 public:
  void  setServers( size_t _amount );
  void  startServers( void );
  void  setWorkerConnections( int _amount );
  int   setPort( int _nServer, int _port );
  int   setName( const std::string& _name );
};
