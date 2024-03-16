/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:33:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 08:32:06 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "BaseParser.hpp"
# include "../Utils.hpp"

class Parser: public BaseParser {
 private:
  vector<string>  **dataServers;
 private:
 public:
  Parser(void);
  ~Parser(void);
  Parser(const Parser&);
  Parser(const string&);
  Parser &operator=(const Parser&);
  void  splitServers(void);
  unsigned int  getServer(int, unsigned int); 
  vector<string> **getDataServers(void) const;
};
