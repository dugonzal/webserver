/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/29 18:30:00 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include  <iostream>
# include <string>
# include <fstream>
# include <cstdlib>
# include <vector>
# include "parser.hpp"

class Server;
class Parser;

class Config {
    
    private :
        const std::string     filename ;
        std::vector<Server*>  servers;
        Parser                parser;
    
    public:
      Config(void);
      Config(std::string _filename);
      ~Config(void);
      void  parseConfig(void);
};
