/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:49:19 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/15 23:28:06 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Location.hpp"
# include "../Logger.hpp"
# include "../Utils.hpp"
# include "Response.hpp"
# include "CGI.hpp"

# define OK 200
# define CREATED 201
# define MOVED 301
# define FOUND 302
# define NOT_FOUND 404
# define METHOD_NOT_ALLOWED 405
# define ENTITY_TOO_LARGE 413
# define VERSION_NOT_SUPPORTED 505

class Response;

class Request {
 private:
  string                header;
  Logger                logger;
  Response              response;
  CGI                   cgi;
  vector<string>        listCookie;

 private:
  map<string, Location> locations;
  Location              locationRoot;
  string                host;
  size_t                port;
  int                   cookie;
  string                setCookie;

 private:
  string  method;
  string  route;
  string  version;
  bool    isCgi;

  ///PRIVATE IKEEEER
  int     clientFd;

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

  void    resHttp500( bool checkErrorPages );
  void    resHttpCGI( const std::string& contentType );
  void    restHttpCustom( int httpCode,const std::string& contentType, const std::string& body );

    // FUNCIONES IKEEEERRRR
  int         checkMethod(const string &_method);
  void        getMethod(void);
  void        postMethod(void);
  void        deleteMethod(void);
  string      replaceAlias(const string& path);
};
