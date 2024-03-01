/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/29 17:32:26 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CONFIG_HPP
# define CONFIG_HPP

# include  <iostream>
# include <string>
# include <fstream>
# include <cstdlib>
# include <vector>
# include "../parser/Parser.hpp"
# include "Server.hpp"
# include "../Signals.hpp"
/*
 * voy a usar el vector de servidores para obtener la data puedo crear una pequeña funcoion que parsee y comprueba 
 * la informcaion dentro del scope del servidor, cada server tendra un vector de string buffer 
 * que recibira el scope del buffer una vez que el scope este parceado
 * */
class Config {
 private:
  Parser                parser;
  Signals               signals;
 private:
  void  setServers(void);
 public:
  Config(void);
 public:
  Config(const string&);
  ~Config(void);
};

# endif
