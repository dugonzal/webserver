/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:33:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/01 12:57:19 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "BaseParser.hpp"
# include "../Utils.hpp"
#include <vector>

class Parser: public BaseParser {
 private:
  vector<string>  *dataServers;
 public:
  Parser(void);
  ~Parser(void);
  Parser(const Parser&);
  Parser(const string&);
  Parser &operator=(const Parser&);
  vector<string> *getDataServers(void) const;
};
