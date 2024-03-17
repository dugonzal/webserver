/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:20:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/17 11:59:03 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Server.hpp"
# include "../parser/Parser.hpp"
# include "../Utils.hpp"

class VirtualServer {
 private:
  vector<Server*>  vServers;
  Parser           parser;
 private:
  void  addServer(Server);
 public:
  VirtualServer(void);
  VirtualServer(const Parser&);
  ~VirtualServer(void);
  VirtualServer(const VirtualServer&);
  VirtualServer &operator=(const VirtualServer&);
 public:
  void  run(void);
};
