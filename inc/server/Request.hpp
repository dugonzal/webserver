/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:54:41 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/20 10:09:00 by jaizpuru         ###   ########.fr       */
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

	/* Server Output Side */
	int							method;
	std::string					_route;
	std::string					fileResponse;
	std::string					httpResponse; // Header for Client
    struct  timeval				timeout;

	public:
		Request( void );
		Request( int _serverFd );
		~Request( void );

		std::string	getRoute( void );
		int		getMethod( void );
};
