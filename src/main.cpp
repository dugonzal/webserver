/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/01/18 02:30:46 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/socket.h>
# include <iostream>


int main(int ac, const char **av) {
      
    if (ac < 2) {
      return (std::cout << "./webserv \"<fileConfig>\"" << std::endl, 0);
    }
    for (int i = 0; i < ac && ++av; i++)
        std::cout << *av << std::endl;
    return (0);
}
