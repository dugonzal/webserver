/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:54:41 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/20 10:35:21 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils.hpp"

#define GET 101
#define DELETE 201
#define POST 301

class Request {
	private:
    /* Client Server Side */
	int							serverFd;
    int							clientFd;
    struct sockaddr_in			clientAddr; // IP socket address
    socklen_t					addrClientLen;

	/* Server Input Side */
    int							returnedBytes;
    char						clientMsg[1028];
	int							inputMethod;
	std::string					inputRoute;
	bool						inputIsGood;

	/* Server Output Side */
	std::string					responseFile;
	std::string					responseHeader; // Header for Client
    struct  timeval				timeout;

	// Variables Iker
	std::string method, file;

	public:
		Request( void );
		Request( int _serverFd );
		~Request( void );

		std::string	getRoute( void );
<<<<<<< HEAD:inc/server/ClientSide.hpp

		// Funciones Iker
		void getMethod( void );
		void postMethod( void );
		void deleteMethod( void );
		void response2client( void );
=======
		int		getMethod( void );
		void	checkHttpVersion( void );
>>>>>>> 97d3457dd8d2674b73061f7526e75e5a30ee412b:inc/server/Request.hpp
};
