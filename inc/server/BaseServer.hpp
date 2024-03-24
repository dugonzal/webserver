/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/24 13:01:17 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/BaseParser.hpp"
# include "../server/Request.hpp"
# include "../Utils.hpp"

class BaseServer {
 protected:
    /* Server Side */
    int                            serverFd; // File Descriptor
    int                            opt; // Special options set for server socket
    struct sockaddr_in             addr; // IP socket address
    socklen_t                      addrLen; // Length of socket
    
    /* Configuration from input */
    int                                 nServers;
    int                                 port;
    std::string                         host;
    std::string                         server_name;
    std::map<int, std::string>          errorPageAr;
    int                                 clientMaxBodySize;

    

 protected:
    map<string, string>            data;
    vector<string>                 error_page;
    vector<string>                 buffer;
    int                            *options;

 public:
    BaseServer(void);
    BaseServer(const BaseServer&);
    BaseServer &operator=(const BaseServer&);
    virtual ~BaseServer(void) = 0;
    virtual BaseServer *clone(void) const = 0;
    void    setServerSide( void );
    void    setRequest( void );

    bool    checkServer( void ) const;
    int     getSocket(void) const;
    int     getNServers( void ) const;

    void    setServerNumber( int _amount );
    void    setPort( int _port );
    void    setHost( std::string& _host );
    void    setServerName( std::string& _name );

  friend ostream &operator<<(ostream&, const BaseServer&);
};
