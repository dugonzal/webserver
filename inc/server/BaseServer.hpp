/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/20 21:22:00 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/BaseParser.hpp"
# include "../server/Request.hpp"
# include "../Utils.hpp"
# include "Location.hpp"

class BaseServer {
 protected:
    /* Server Side */
    int                            serverFd; // File Descriptor
    const int                      opt; // Special options set for server socket
    struct sockaddr_in             addr; // IP socket address
    socklen_t                      addrLen; // Length of socket
    /* Configuration from input */
    size_t                         nServers;
    size_t                         port;
    string                         host;
    string                         server_name;
    int                            clientMaxBodySize;
    map<string, Location>          location;
    Location                       LocationRoot;
    vector<string>                 buffer;

 public:
    BaseServer(void);
    BaseServer(const BaseServer&);
    BaseServer &operator=(const BaseServer&);
    virtual ~BaseServer(void) = 0;
////    virtual BaseServer clone(void) const = 0;
    void          setServerSide(void);
    void          setRequest(void);
    void          setLocations(const map<string, Location>&);
    int           getSocket(void) const;
    size_t        getNServers(void) const;
    Location      getLocation(void) const;
    const string  getHost(void) const;
    int           getPort(void) const;
  friend ostream  &operator<<(ostream&, const BaseServer&);
};
