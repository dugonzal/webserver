/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/12 12:24:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include  <iostream>
# include <string>
# include <fstream>
# include <cstdlib>
# include <vector>
# include "../parser/parser.hpp"
# include "Server.hpp"

namespace ft {
    class Config;
}

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

