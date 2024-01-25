/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/25 09:59:45 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server.hpp"
# include "../inc/config.hpp"

/* necesito extraer los datos de configuracion 
 * he creado una clase llamada config que le voy a pasar \
 * el argumento y voy a leer y parsear la data para server
 *
 * */
int main(int ac, const char **av) {

  if (ac != 2)
    return (std::cout << "./webserv \"<fileConfig>\"" << std::endl, 0);
  
  try {
       
    Server webserv;

    (void)webserv;
    
  } catch (std::exception &e) 
      { std::cout << "Error " << e.what() << std::endl; }
    
    for (int i = 0; i < ac && ++av; i++)
      std::cout << *av << std::endl;
   
    return (0);
}
