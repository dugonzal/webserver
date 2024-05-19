/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:46:17 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/19 10:30:26 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class Request;

class Response: private virtual Utils {
 private:
 public:
  Response(void);
  ~Response(void);
  static bool sendResponse(const string&, int fd);
};
