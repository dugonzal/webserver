/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:46:17 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/22 17:53:16 by Dugonzal         ###   ########.fr       */
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
  void  print(void) {
    cout << "hola mundo" << endl;
  }
};
