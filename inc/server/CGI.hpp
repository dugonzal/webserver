/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:39:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/19 10:29:56 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"
# include "../Logger.hpp"

class CGI: private virtual Utils {
 private:
  vector<string>    result;
  ifstream  file;
  string    path;
  string    fileName;
  string    tempFileName;
  string    root;
  Logger    logger;

  map<string, string> query;

 private:
  CGI(const CGI&);
  CGI &operator=(const CGI&);

 public:
  CGI(void);
  ~CGI(void);

 private:
  void    clear(void);

 public:
  void    setCgi(const string&, const string&);
  void    handlerCgi( bool isQuery );
  const vector<string>&  getCgi(void) const;

  void    insertQuery( void );
  void    setQuery( const map<string, string> queryTmp );
};
