/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:49:19 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 20:54:19 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"
# include "Location.hpp"
# include "Response.hpp"
# include "Logger.hpp"

class Location;
class Response;

class Request {
 private:
  string                header;
  map<string, Location> locations;
  Location              locationRoot;
  Logger                logger;
  Response              response;

/* New implementations */
	int					clientFd;
	int					returnedBytes;
	int					inputMethod;
	string				inputRoute;
	bool					inputIsGood;
	string				responseFile;
	string				responseHeader; // Header for Client
	string				method, file;

 public:
	Request(void);
	~Request(void);
	Request(const Request&);
	Request &operator=(const Request&);
	void    setHeader(const char *);
	void  	setClientFd( int _clientFd );
	void    setLocation(const map<string, Location>&, const Location&);
	void    handlerRequest(void);

	int		parseClientMsg(void);
	// Parsing input
	int		getMethodType(void);
	string	getRoute(void);
	void	checkHttpVersion(void);
	void  tmp(void);
	// Funciones Iker
	void methodGet(void);
	void methodPost(void);
	void methodDelete(void);
};
