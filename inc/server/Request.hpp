/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:49:19 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/22 17:13:33 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"
# include "Location.hpp"
# include "../Logger.hpp"

class Location;

class Request {
 private:
  string                header;
  Logger                logger;

 private:
  map<string, Location> locations;
  Location              locationRoot;

 private:
  string  method;
  string  route;
  string  version;
  bool    isCgi;

 public:
  Request(void);
  ~Request(void);
  Request(const Request&);
  Request &operator=(const Request&);
  void    setHeader(const char *);
  void    setLocation(const map<string, Location>&);
  bool    setMethod(const string&);
  bool    setRouteAndVersion(const string&);
  void    setLocation(void);
  void    handlerRequest(void);
  void    parserData(void);
// private:
};
