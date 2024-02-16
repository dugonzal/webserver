/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/13 01:12:25 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "BaseServer.hpp"

class Server: public BaseServer {
  
  protected:
//    Server(const Server&);
 //   Server &operator=(const Server&);
  
  public:
    Server(void);
    ~Server(void);
    BaseServer *clone(void) const;
};
