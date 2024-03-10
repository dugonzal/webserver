/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/10 20:45:29 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/BaseParser.hpp"
# include "../Utils.hpp"

class BaseServer {
 protected:
    struct sockaddr_in             addr; // Server
    socklen_t                      addrLen; // Length of socket
    
    struct sockaddr_in             clientAddr; // Client
    socklen_t                      addrClientLen;
    char                           clientMsg[1028];
    
    int                            s; // serverSocket fd
    int                            opt; // Special options set for server socket
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
    int     createSocket(void);
    bool    checkServer( void ) const;

    int     getSocket(void) const;
    void    setServer(void);
    void    setWConnections( int _amount );
    void    setPort( int _port );
    void    setServerName( const std::string& _sName );

  friend ostream &operator<<(ostream&, const BaseServer&);
};
