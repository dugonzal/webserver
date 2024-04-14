/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/14 12:32:19 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "BaseServer.hpp"
# include "../Utils.hpp"

class Server: public virtual BaseServer {
 private:
  Request   request;
  list<int> clients;
  //Response response;

 public:
    Server(void);
    ~Server(void);
    Server(const Server&);
    Server &operator=(const Server&);
    Server clone(void) const;
};
