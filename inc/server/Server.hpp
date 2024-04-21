/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 16:04:09 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "BaseServer.hpp"
# include "../Utils.hpp"

class Server: public virtual BaseServer {
 private:
  Request     request;
  //Response  response;

 public:
  Server(void);
  ~Server(void);
  Server(const Server&);
  Server  &operator=(const Server&);
  void    handlerClient(size_t, const char *);
  void    handlerRequest(const char *);
  void    handlerResponse(size_t);
  void    setLocationRequest(void);
};
