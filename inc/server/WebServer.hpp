/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/20 17:14:00 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Signals.hpp"
#include "../Utils.hpp"
#include "../parser/Parser.hpp"
#include "../server/ServerManager.hpp"

class WebServer : private virtual Utils {
private:
  mutable ServerManager servers;
  mutable Parser parser;
  mutable Signals signals;
  mutable size_t nServers;
  mutable map<string, Location> *locations;
  Logger logger;

private:
  WebServer(void);

private:
  void handlerSetServerWebServer(void);
  void setLocations(const vector<string> &, size_t);
  void insertLocation(Location *, const string &);

public:
  explicit WebServer(const string &);
  WebServer(const WebServer &);
  WebServer &operator=(const WebServer &);
  ~WebServer(void);
  void setServer(void);
};
