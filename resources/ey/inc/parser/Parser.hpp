/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:33:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/14 12:11:07 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "BaseParser.hpp"
# include "../Utils.hpp"

class Parser: public BaseParser {
 private:
  mutable vector<string>  *dataServers;

 public:
  Parser(void);
  explicit Parser(const string&);
  ~Parser(void);
  Parser(const Parser&);
  Parser &operator=(const Parser&);
  const vector<string> *getDataServers(void) const;
};
