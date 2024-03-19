/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSide.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:54:41 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/19 12:26:44 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils.hpp"

class ClientSide {
	private:
    /* Client Server Side */
    int							clientFd;
    struct sockaddr_in			clientAddr; // IP socket address
    socklen_t					addrClientLen;

	/* Client Message Side */
    int							returnedBytes;
	std::string					askedRoute;
    char						clientMsg[1028];
	std::string					serverResponse; // Header for Client
    struct  timeval				timeout;

	public:
		ClientSide( void );
		ClientSide( int _serverFd );
		~ClientSide( void );

		int 	openFile( const std::string& _route );
		void	setRoute( void );
};
