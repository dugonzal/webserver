/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/03 09:23:45 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef  SERVER_HPP
# define  SERVER_HPP

# include "BaseServer.hpp"


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
