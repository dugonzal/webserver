/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/20 11:54:44 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "BaseServer.hpp"
# include "../Utils.hpp"
# include "Request.hpp"
# include "Response.hpp"

class Request;
class Response;

class Server: public virtual BaseServer {
 private:
  Request   request;
  Response  response;

 public:
  Server(void);
  ~Server(void);
  Server(const Server&);
  Server  &operator=(const Server&);
  void    handlerClient(size_t, const char *);
  void    setLocationRequest(void);
  void    setEnviroment( char** _environ );
};
