/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/15 17:29:48 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/BaseParser.hpp"
# include "../Utils.hpp"

class BaseServer {
 protected:
    /* Server Side */
    int                            *serverFd; // File Descriptor
    int                            opt; // Special options set for server socket
    struct sockaddr_in             *addr; // IP socket address
    socklen_t                      *addrLen; // Length of socket
    std::string                    serverResponse; // Header for Client

   /* File Descriptor Sets, blocks made to store FDs */
   fd_set	cSockets;
   fd_set   rSockets;
   fd_set   wSockets;

    /* Client Side */
    int                            clientFd;
    struct sockaddr_in             clientAddr; // IP socket address
    socklen_t                      addrClientLen;
    char                           clientMsg[1028];
    struct  timeval                timeout;
    
    /* Configuration from input */
    int                            nServers;
    std::deque<int>                 port;
    std::deque<string>                 host;
    std::vector<std::string>            server_name;
    std::map<int, std::string>          errorPageAr;
    std::vector<int>               clientMaxBodySize;

    

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
    int     setServer( void );
    void    setServerSide( int _port );
    void    setClientSide( int socket );
    void    setSelect( void );

    bool    checkServer( int _nServer ) const;
    int     *getSockets(void) const;
    int     getNServers( void ) const;

    void    setServerNumber( int _amount );
    void    setPort( std::deque<int> &_portAr );
    void    setHost( std::deque<string> &_host );
    void    setServerName( const std::vector<string> &_sName );

  friend ostream &operator<<(ostream&, const BaseServer&);
};
