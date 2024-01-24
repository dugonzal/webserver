/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/24 15:44:06 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <ostream>
# include <sys/socket.h>
# include <iostream>
# include <string>
# include <exception>
// hacer la class otrtodoxa romana
class Config;

class server {
    
    private:
        const   std::string  host;
        int                  port;
        int                 socket;
        int                 fd;
        typedef struct sockaddr_in  addr;
    
    public:
      server(void);
      ~server(void);
       server(const std::string &host, int &port);
      server(const server &copy);
      server &operator=(const server &copy);
};


// imprimir informacion relevante de la clase server que en este caso sera la  clase base
std::ostream &operator<<(std::ostream &out, const server &webserv);

