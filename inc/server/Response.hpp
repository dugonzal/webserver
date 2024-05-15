/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:46:17 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/15 23:22:37 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class Request;

class Response {
 private:
 public:
  Response(void);
  ~Response(void);
  static bool sendResponse(const string&, int fd);
  //const string  &resHttp302(void);  
};
