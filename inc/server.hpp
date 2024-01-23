/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/22 11:32:09 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <ostream>
# include <sys/socket.h>
# include <iostream>
#include <string>
// hacer la class otrtodoxa romana

class server {
    
    private:
        std::string   host;
        int           port;
    
    public:
      server(void);
      ~server(void);
       server(const std::string &host, int &port);
      server(const server &copy);
      server &operator=(const server &copy);
};


// imprimir informacion relevante de la clase server que en este caso sera la  clase base
std::ostream &operator<<(std::ostream &out, const server &webserv);

