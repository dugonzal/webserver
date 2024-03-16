/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 08:50:41 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Config.hpp"

int main(int ac, const char **av, const char **) {
  if (ac != 2)
      av[1] = "conf/default.conf";
  try {
    Config  config(*(++av));
  } catch (std::exception &e)
      { std::cout << "Error: " << e.what() << std::endl; }
  return (0);
}
