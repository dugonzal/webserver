/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:47 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/07 06:53:52 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../parser/Parser.hpp"
# include "../Signals.hpp"
# include "Server.hpp"
# include "../Utils.hpp"
# include "../server/VirtualServer.hpp"

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

 private:
  void  setServers(void);

 public:
  Config(const string&);
  Config(const Config&);
  Config &operator=(const Config&);
  ~Config(void);
};
