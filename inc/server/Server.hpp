/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 19:54:58 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "BaseServer.hpp"
# include "../Utils.hpp"

class Server: public virtual BaseServer {
 private:
  
  Request    request;

 public:
  Server(void);
  ~Server(void);
  Server(const Server&);
  Server  &operator=(const Server&);
  void    handlerClient(size_t, const char *);
  void    handlerRequest(const char *, int);
  void    handlerResponse(size_t);
  void    setLocationRequest(void);
};
