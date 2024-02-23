/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/23 13:58:05 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <unistd.h>
# include <map>
# include <string>
# include <iostream>
# include <vector>
# include <fstream>
# include <cstdlib>
# include <cassert>

# include "../utils.hpp"

class Parser {
 private:
    std::string               filename;
    std::size_t               nServers;
    std::vector<std::string>  data;
 private:
    void  handlerError(void);
    std::vector<std::string>::iterator  \
      &serverError(std::vector<std::string>::iterator &);
 public:
    Parser(void);
    Parser(const std::string &);
    ~Parser(void);
    void  readIncludeError(std::string);
    void  readInclude(std::string);
    void  printData(void);
};
