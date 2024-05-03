/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:49:19 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/03 17:36:41 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Location.hpp"
# include "../Logger.hpp"
# include "../Utils.hpp"
# include "Response.hpp"
# include "CGI.hpp"

class Response;

class Request {
 private:
  string                header;
  Logger                logger;
  Response              response;
  CGI                   cgi;

 private:
  map<string, Location> locations;
  Location              locationRoot;
  string                host;
  size_t                port;

 private:
  string  method;
  string  route;
  string  version;
  bool    isCgi;

  ///PRIVATE IKEEEER
  int     clientFd;
  string  autoDirectory;

 public:
  Request(void);
  ~Request(void);
  Request(const Request&);
  Request &operator=(const Request&);
  void    setHeader(const char *);
  void    setLocation(const map<string, Location>&);
  void    setHostAndPort(const string&, size_t);
  bool    setMethod(const string&);
  bool    setRouteAndVersion(const string&);
  void    setLocation(void);
  void    handlerRequest(void);
  void    parserData(void);
  void    serverToClient(const string&, size_t);

    // FUNCIONES IKEEEERRRR
  int         checkMethod(const string &_method);
  void        getMethod(void);
  void        postMethod(void);
  void        deleteMethod(void);
  string      replaceAlias(const string& path);
};
