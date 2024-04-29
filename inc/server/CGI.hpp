/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:39:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/29 10:21:50 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"
# include "../Logger.hpp"

class CGI {
 private:
  string    result;
  string    cmdOutput;
  ifstream  file;
  string    path;
  string    fileName;
  string    root;
  Logger    logger;

 private:
  CGI(const CGI&);
  CGI &operator=(const CGI&);

 public:
  CGI(void);
  ~CGI(void);
  void          setCgi(const string&, const string&);
  const string  handlerCgi(void);
  void          clear(void);

  std::string getCgi( void ) const;
};
