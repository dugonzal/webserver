/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/12 12:23:37 by Dugonzal         ###   ########.fr       */
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
#include "../parser/parser.hpp"
// hacer la class otrtodoxa romana

class BaseServer {
    private:
      struct sockaddr_in                  addr;
      const  std::string                  host;
      int                                 port;
      int                                 s;
      int                                 fd;
      std::map<std::string, std::string>  data;
      std::string                         *error_page;
      std::string                         *buffers;
      int                                 *options;
    // uso estos dos punteros uno para las paginas de error y otro para los buffers de enviar y recibir
    public:
        BaseServer(void);
        virtual ~BaseServer(void)  = 0;
        BaseServer(const std::string&, int );
        BaseServer(const BaseServer&);
        BaseServer &operator=(const BaseServer&);
        void   setServer(void);
        virtual BaseServer *clone(void) const = 0;
};
// imprimir informacion relevante de la clase server que en este caso sera la  clase base
std::ostream &operator<<(std::ostream&, const BaseServer&);
