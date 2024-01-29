/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/30 00:21:44 by Dugonzal         ###   ########.fr       */
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
        const std::string           filename;
        std::vector<Server*>        servers;
        std::vector<std::string>    data; 
        // voy a usar un vector de string para guardar la informacion del archivo de configuracion 
    
    public:
        Parser                      parser; 
    
    public:
      Config(void);
      Config(std::string _filename);
      ~Config(void);
};
