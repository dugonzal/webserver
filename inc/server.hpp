/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/29 23:49:39 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <ostream>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <iostream>
# include <string>
# include <exception>
# include <cstdlib>
# include <cstring>
# include <sys/un.h>
# include "config.hpp"
#include "parser.hpp"
// hacer la class otrtodoxa romana
//class Config;

class Server {
    
    private:
        struct sockaddr_in                  addr;
        const  std::string                  host;
        int                                 port;
        int                                 s;
        int                                 fd;
        std::map<std::string, std::string>  data;

    public:
        Server(void);
        ~Server(void);
        Server(const std::string &_host, int _port);
        Server(const Server &copy);
        Server &operator=(const Server &copy);
        void   setServer(void);

};
// imprimir informacion relevante de la clase server que en este caso sera la  clase base
std::ostream &operator<<(std::ostream &out, const Server &webserv);
