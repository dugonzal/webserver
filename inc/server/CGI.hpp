/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:39:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/20 12:04:07 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"
# include "../Logger.hpp"

class CGI: private virtual Utils {
 private:
  char**    environ;
  string    result;
  ifstream  file;
  string    path;
  string    fileName;
  string    root;
  Logger    logger;

  string query;

 private:
  CGI(const CGI&);
  CGI &operator=(const CGI&);

 public:
  CGI(void);
  ~CGI(void);

 private:
  void    clear(void);

 public:
  void    setCgi(const string&, const string&, char** );
  void	  setQuery( string& _query );
  void    handlerCgi( void );
  const string&  getCgi(void) const;
};
