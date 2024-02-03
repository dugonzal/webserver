/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/03 23:43:58 by Dugonzal         ###   ########.fr       */
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
        std::vector<Server*>        servers;
        // voy a usar un vector de string para guardar la informacion del archivo de configuracion 
    
    public:
        Parser                      parser; 
    
    public:
      Config(void);
      ~Config(void);
};
