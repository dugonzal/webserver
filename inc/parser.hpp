/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/04 15:32:32 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <map> 
# include <string>
# include <iostream>
# include <vector>
# include <fstream>
# include <unistd.h>

class Parser {
  
  private:
    std::string  filename; 
    std::vector<std::string>  data;

  private:
    void  handlerError(void);
    std::vector<std::string>::iterator  &serverError(std::vector<std::string>::iterator &); 
  public:
    Parser(void);
    Parser(const std::string &_filename);
    ~Parser(void);
    void  parser(void);
};
