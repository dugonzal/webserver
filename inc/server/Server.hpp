/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/09 17:12:03 by Dugonzal         ###   ########.fr       */
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
  void    handlerClient(size_t, const char *, bool);
  void    handlerRequest(const char *);
  void    handlerResponse(size_t);
  void    setLocationRequest(void);
};
