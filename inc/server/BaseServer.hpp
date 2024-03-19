/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:35 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/BaseParser.hpp"
# include "../server/ServerParser.hpp"
# include "../Utils.hpp"

class BaseServer {
 protected:
   ServerParser                    *parser;
    /* Server Side */
    int                            serverFd; // File Descriptor
    int                            opt; // Special options set for server socket
    struct sockaddr_in             addr; // IP socket address
    socklen_t                      addrLen; // Length of socket
    std::string                    serverResponse; // Header for Client

    /* Client Side */
    int                            clientFd;
    struct sockaddr_in             clientAddr; // IP socket address
    socklen_t                      addrClientLen;
    char                           clientMsg[1028];
    struct  timeval                timeout;
    
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
    void    setClientSide( void );

    bool    checkServer( void ) const;
    int     getSocket(void) const;
    int     getNServers( void ) const;

    void    setServerNumber( int _amount );
    void    setPort( int _port );
    void    setHost( std::string& _host );
    void    setServerName( std::string& _name );

  friend ostream &operator<<(ostream&, const BaseServer&);
};
