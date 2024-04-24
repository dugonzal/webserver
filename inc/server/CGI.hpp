/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:39:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/24 22:27:31 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class CGI {
 private:
  string    result;
  ifstream  file;
  string    path;

 private:
  CGI(const CGI&);
  CGI &operator=(const CGI&);

 public:
  CGI(void);
  ~CGI(void);
};
