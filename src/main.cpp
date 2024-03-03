/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/03 10:03:56 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server/BaseServer.hpp"
# include "../inc/server/Config.hpp"

/* necesito extraer los datos de configuracion 
 * he creado una clase llamada config que le voy a pasar \
 * el argumento y voy a leer y parsear la data para server
 *
 * */
int main(int ac, const char **av, const char **) {
  if (ac != 2)
      av[1] = "conf/default.conf";
  try {
    Config  config(*(++av));
  } catch (std::exception &e)
      { std::cout << "Error: " << e.what() << std::endl; }
  return (0);
}
