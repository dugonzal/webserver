/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 14:51:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "BaseServer.hpp"
# include "../Utils.hpp"
# include "Logger.hpp"

class Server: public virtual BaseServer {
 private:
  Request     request;
  //Response  response;
  Logger      logger;

 public:
  Server(void);
  ~Server(void);
  Server(const Server&);
  Server  &operator=(const Server&);
  void    handlerClient(size_t, const char *);
  void    handlerRequest(const char *);
  void    handlerResponse(size_t);
  void    setLocationRequest(void);
  void    setLogger(const Logger&);
};
