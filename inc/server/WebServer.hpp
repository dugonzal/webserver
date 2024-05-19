/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/19 10:31:31 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/Parser.hpp"
# include "../Signals.hpp"
# include "../Utils.hpp"
# include "../server/ServerManager.hpp"

class WebServer: private virtual Utils {
 private:
  mutable ServerManager         servers;
  mutable Parser                parser;
  mutable Signals               signals;
  mutable size_t                nServers;
  mutable map<string, Location> *locations;
  Logger                        logger;
 
 private:
  WebServer(void);

 private:
  void    setServerWebServer(const vector<string>&, size_t);
  void    handlerSetServerWebServer(void);
  void    setLocations(const vector<string>&, size_t); 
  void    insertLocation(Location*, const string&);

 public:
  explicit WebServer(const string&);
  WebServer(const WebServer&);
  WebServer &operator=(const WebServer&);
  ~WebServer(void);
  void  setServer(void);
};
