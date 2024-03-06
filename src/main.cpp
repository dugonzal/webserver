/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/06 16:27:41 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server/BaseServer.hpp"
# include "../inc/server/Config.hpp"

int main(int ac, const char **av, const char **) {
  if (ac != 2) // if no argument is given
      av[1] = "conf/default.conf";
  try {
    /* Config is the base object for the project */
    Config  config(*(++av));
  } catch (std::exception &e)
      { std::cout << "Error: " << e.what() << std::endl; }
  return (0);
}
