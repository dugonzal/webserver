/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/12 12:10:37 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/BaseParser.hpp"
# include "../Utils.hpp"

class BaseServer {
 protected:
    /* Server Side */
    int                            serverFd; // File Descriptor
    int                            opt; // Special options set for server socket
    struct sockaddr_in             addr; // Structure to hold addresses
    socklen_t                      addrLen; // Length of socket
    std::string                    serverResponse; // Header for Client
    
   /* Select */
   fd_set	cSockets;
   fd_set   rSockets;
   fd_set   wSockets;

    /* Client Side */
    int                            clientFd;
    struct sockaddr_in             clientAddr; // Client
    socklen_t                      addrClientLen;
    char                           clientMsg[1028];
    struct  timeval                timeout;
    
    /* Configuration from input */
    int                            port;
    std::string                    server_name;
    int                            wConnections; // Number of working connections (maybe not neccessary)

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
    void    setServerSide( void );
    void    setClientSide( void );
    void    setSelect( void );

    bool    checkServer( void ) const;
    int     getSocket(void) const;
    void    setWConnections( int _amount );
    void    setPort( int _port );
    void    setServerName( const std::string& _sName );

  friend ostream &operator<<(ostream&, const BaseServer&);
};
