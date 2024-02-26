/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/26 16:25:04 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/parser.hpp"
# include "../utils.hpp"

/*
namespace ft {
    class BaseServer;
}*/

class BaseServer {
 protected:
    struct sockaddr_in                  addr;
    socklen_t                           addrLen;
    const  string                       host;
    int                                 port;
    int                                 s;
 protected:
    BaseServer(std::vector<string>);
    std::map<string, string>            data;
    std::vector<string>                 error_page;
    std::vector<string>                 buffer;
    int                                 *options;
    int                                 opt;
 public:
    BaseServer(void);
    virtual ~BaseServer(void) = 0;
    virtual BaseServer *clone(void) const = 0;
    void  setServer(void);
    int   setSocket(void);
    int   getSocket(void) const;
  friend std::ostream &operator<<(std::ostream&, const BaseServer&);
};
