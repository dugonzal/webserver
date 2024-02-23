/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/23 16:23:21 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <functional>
#include <stdexcept>
# include <unistd.h>
# include <map>
# include <string>
# include <iostream>
# include <vector>
# include <fstream>
# include <cstdlib>
# include <cassert>
# include "../utils.hpp"
using std::cout;
using std::endl;
using std::string;
using  std::runtime_error ;
using   std::logic_error ;

class Parser {
 private:
    std::string               filename;
    std::size_t               nServers;
    std::vector<string>  data;
 private:
    void  handlerError(void);
    std::vector<string>::iterator  \
      &serverError(std::vector<string>::iterator &);
 public:
    Parser(void);
    Parser(const string &);
    ~Parser(void);
    void  readIncludeError(string);
    void  readInclude(string);
    void  printData(void);
};
