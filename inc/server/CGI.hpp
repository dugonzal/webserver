/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:39:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/04 13:47:27 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"
# include "../Logger.hpp"

class CGI {
 private:
  vector<string>    result;
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

 private:
  void    readFd(const string&);
  void    clear(void);

 public:
  void    setCgi(const string&, const string&);
  void    handlerCgi(void);
  const vector<string>&  getCgi(void) const;
};
