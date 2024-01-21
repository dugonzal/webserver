/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/18 02:51:09 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <ostream>
# include <sys/socket.h>
# include <iostream>
#include <string>
// hacer la class otrtodoxa romana

class webserv {
    private:
        std::string   host;
        int           port;
    
    public:
      webserv();
      ~webserv();
       webserv(const std::string &host, int &port);
      webserv(const webserv &copy);
      webserv &operator=(const webserv &copy);
};


// imprimir informacion relevante de la clase server que en este caso sera la  clase base
std::ostream &operator<<(std::ostream &out, const webserv &webserv);

