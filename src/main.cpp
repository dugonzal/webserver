/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/22 09:01:30 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server/WebServer.hpp"

int main(int ac, const char **av, const char **) {
  if (ac != 2)
      av[1] = "conf/default.conf";
  try {
    WebServer  webserver(*(++av));

    webserver.setServer();
  } catch (std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
  return (0);
}
