/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:33:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/02 18:16:34 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "BaseParser.hpp"
# include "../Utils.hpp"

class Parser: public BaseParser {
 private:
  vector<string>  *dataServers;
 public:
  Parser(void);
  explicit Parser(const string&);
  ~Parser(void);
  Parser(const Parser&);
  Parser &operator=(const Parser&);
  vector<string> *getDataServers(void) const;
};
