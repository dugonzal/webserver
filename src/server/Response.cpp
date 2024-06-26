/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:48:59 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/15 23:28:31 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Response.hpp"

Response::Response(void) { }

Response::~Response(void) { }
  
bool Response::sendResponse(const string &header, int fd) {
  if (send(fd, header.data(), header.size(), 0) < 0)
    return (true);
  return (false);
}
  
