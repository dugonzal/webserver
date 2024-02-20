/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/20 18:33:54 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <map> 
# include <string>
# include <iostream>
# include <vector>
# include <fstream>
# include <unistd.h>
# include <cstdlib>
# include <cassert>

class Parser {  
  
  private:
  std::size_t    NS;
    std::string  filename; 
    std::vector<std::string>  data;
   
  private:
    void  handlerError(void);
    std::vector<std::string>::iterator  &serverError(std::vector<std::string>::iterator &); 
  
  public:
    Parser(void);
    Parser(const std::string&);
    ~Parser(void);
    void  readIncludeError(std::string);
    void  readInclude(std::string);
    void  getInclude(void);
};
