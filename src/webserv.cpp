/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/30 00:26:48 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server.hpp"
# include "../inc/config.hpp"

/* necesito extraer los datos de configuracion 
 * he creado una clase llamada config que le voy a pasar \
 * el argumento y voy a leer y parsear la data para server
 *
 * */
int main(int ac, char const **av) {

  if (ac != 2)
      av[1] = "nginx/conf/default.conf";
  
  try {
    Config              config(*(++av));

    (void)config;
    config.parser.parser();
  } catch (std::exception &e) 
      { std::cout << "Error: " << e.what() << std::endl; }
    
    return (0);
}
