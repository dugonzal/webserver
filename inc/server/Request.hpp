/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:54:41 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/04/14 12:27:27 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils.hpp"

#define GET 101
#define DELETE 201
#define POST 301

class Request {
	private:
    /* Client Server Side */
    int							clientFd;
    struct sockaddr_in			clientAddr; // IP socket address
    socklen_t					addrClientLen;

	/* Server Input Side */
    int							returnedBytes;
    char						clientMsg[1028];
	  int							inputMethod;
    string					inputRoute;
	  bool						inputIsGood;

	/* Server Output Side */
	  string					responseFile;
	  string					responseHeader; // Header for Client
    struct  timeval				timeout;

	// Variables Iker
	  string method, file;

	public:
		Request(void);
		Request(int _serverFd);
		~Request(void);

		int		parseClientMsg(void);
		// Parsing input
		int		getMethodType(void);
		string	getRoute(void);
		void	checkHttpVersion(void);

		// Funciones Iker
		void methodGet(void);
		void methodPost(void);
		void methodDelete(void);
};
