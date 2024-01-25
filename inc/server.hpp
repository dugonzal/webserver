/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/25 10:28:26 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <ostream>
# include <sys/socket.h>
# include <iostream>
# include <string>
# include <exception>
# include <cstdlib>

// hacer la class otrtodoxa romana
class Config;

class Server {
    
    private:
        const   std::string         host;
        int                         port;
        int                         socket;
        int                         fd;
        typedef struct sockaddr_in  addr;
  public:
        Server(void);
        ~Server(void);
        Server(const std::string &host, int &port);
        Server(const Server &copy);
        Server &operator=(const Server &copy);
};

// imprimir informacion relevante de la clase server que en este caso sera la  clase base
std::ostream &operator<<(std::ostream &out, const Server &webserv);
