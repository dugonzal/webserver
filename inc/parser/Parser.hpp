/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:33:53 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/03 13:46:05 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "BaseParser.hpp"
# include "../Utils.hpp"

class Parser: public BaseParser {
// private:

  public:
    Parser(void);
    Parser(const string&);
    ~Parser(void);
    Parser(const Parser&);
    Parser &operator=(const Parser&);
};
