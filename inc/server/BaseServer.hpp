/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/18 16:13:22 by Dugonzal         ###   ########.fr       */
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
# include <cassert>
#include "../parser/parser.hpp"
// hacer la class otrtodoxa romana
namespace ft {
  class BaseServer;
}

class BaseServer {
  protected:
    struct sockaddr_in                  addr;
    const  std::string                  host;
    int                                 port;
    int                                 s;
    socklen_t                           addrLen; 
  protected:
    std::map<std::string, std::string>  data;
    std::vector<std::string>            error_page;
    std::vector<std::string>            buffers;
    int                                 *options;
    int                                 opt;
  //protected:
  //   BaseServer(const BaseServer&);
  //  BaseServer &operator=(const BaseServer&);
  friend std::ostream &operator<<(std::ostream&, const BaseServer&);
  
  public:
    BaseServer(void);
    virtual ~BaseServer(void) = 0;
    virtual BaseServer *clone(void) const = 0;
    BaseServer(const std::string&, int);
    void  setServer(void);
    int   setSocket(void);
    int   getSocket(void) const;
};
