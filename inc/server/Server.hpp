/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 14:57:20 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "BaseServer.hpp"

class Server: public BaseServer {
 private:
  list<int>     clients;
 public:
    Server(void);
    Server(const vector<string>&);
    ~Server(void);
    Server(const Server&);
    Server &operator=(const Server&);
    void  getServer(void) const;
    Server *clone(void) const;
};
