/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:46:17 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/20 21:50:05 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class Response {
 private:
  string  response;

 public:
  Response(void);
  ~Response(void);
  Response(const Response&);
  Response operator=(const Response&);
};
