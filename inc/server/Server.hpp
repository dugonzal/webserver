/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/29 17:37:14 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef  SERVER_HPP
# define  SERVER_HPP

# include "BaseServer.hpp"
# include "Config.hpp"

class Server: public BaseServer {
 private:
//    Server(const Server&);
 //   Server &operator=(const Server&);
 public:
    Server(void);
    ~Server(void);
    void  getServer(void) const;
  BaseServer *clone(void) const;
};

#endif
