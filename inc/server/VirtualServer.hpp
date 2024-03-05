/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/05 12:09:04 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Server.hpp"
# include "../Utils.hpp"

class VirtualServer {
 private:
  vector<Server*>  vServers;

 public:
  VirtualServer(void);
  ~VirtualServer(void);
  VirtualServer(const VirtualServer&);
  VirtualServer &operator=(const VirtualServer&);
 public:
  void  addServer(Server);
};
