/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:42:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/29 17:31:55 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef  BASESERVER_HPP
# define  BASESERVER_HPP

# include "../parser/Parser.hpp"
# include "../Utils.hpp"

class BaseServer {
 protected:
    struct sockaddr_in                  addr;
    socklen_t                           addrLen;
    int                                 s;
 protected:
    std::map<string, string>            data;
    std::vector<string>                 error_page;
    std::vector<string>                 buffer;
    int                                 *options;
    int                                 opt;
 public:
    BaseServer(std::vector<string>);
    BaseServer(void);
    virtual ~BaseServer(void) = 0;
    virtual BaseServer *clone(void) const = 0;
    void  setServer(void);
    int   setSocket(void);
    int   getSocket(void) const;
  friend std::ostream &operator<<(std::ostream&, const BaseServer&);
};

# endif
