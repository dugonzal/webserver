/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 09:35:25 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "parser/Parser.hpp"
# include "Signals.hpp"
# include "server/Server.hpp"
# include "Utils.hpp"
# include "server/VirtualServer.hpp"

/*
 * voy a usar el vector de servidores para obtener la data puedo crear una pequeña funcoion que parsee y comprueba 
 * la informcaion dentro del scope del servidor, cada server tendra un vector de string buffer 
 * que recibira el scope del buffer una vez que el scope este parceado
 * */
class Config {
 private:
  VirtualServer servers;
  Parser        parser;
  Signals       signals;

 private:
  Config(void);

 public:
  Config(const string&);
  Config(const Config&);
  Config &operator=(const Config&);
  ~Config(void);
};
