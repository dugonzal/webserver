/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:46:17 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 19:30:24 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class Request;

class Response {
 private:
  Request*  ptrData;
  string    response;

 public:
  Response(void);
  ~Response(void);
  Response(const Response&);
  Response    operator=(const Response&);
  void	      setPtrRequest( Request* ptr );
  Request*	  getPtrData( void ) const;
  std::string	getResponse( void ) const;
};
