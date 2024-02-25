/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/25 19:27:58 by Dugonzal         ###   ########.fr       */
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
# include "../Signals.hpp"
/*
namespace ft {
    class Config;
}
*/
//template<class T = class std::vector<Server*> >
class Config {
 private:
  //    T                          _servers;  // voy a usar un vector de punteros a Server para guardar la informacion del archivo de configuracion
        // voy a usar un vector de string para guardar la informacion del archivo de configuracion 
      std::vector<std::string>    _data;
 public:
 //      Signals                     signals;      
        Parser                      parser; 
 public:
      Config(void);
      ~Config(void);
};

