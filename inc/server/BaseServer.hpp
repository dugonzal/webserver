/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 15:03:58 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/ServerParser.hpp"
# include "../Utils.hpp"

class BaseServer {
 protected:
    ServerParser         sParser;
    struct sockaddr_in   addr;
    socklen_t            addrLen;
    int                  s;
    int                  opt;
    std::list<int>       client;
 protected:
    map<string, string>  data;
    vector<string>       error_page;
    int                  *options;

 public:
    BaseServer(void);
    BaseServer(const vector<string>&);
    BaseServer(const BaseServer&);
    BaseServer &operator=(const BaseServer&);
    virtual ~BaseServer(void) = 0;
    virtual BaseServer *clone(void) const = 0;
    void  setServer(void);
    int   createSocket(void);
    int   getSocket(void) const;

  friend ostream &operator<<(ostream&, const BaseServer&);
};
