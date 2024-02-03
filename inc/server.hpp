/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/30 17:44:49 by Dugonzal         ###   ########.fr       */
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
        std::string                         *error_page;
        std::string                         *buffers;

    // uso estos dos punteros uno para las paginas de error y otro para los buffers de enviar y recibir
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
