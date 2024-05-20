/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/20 12:00:04 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server/WebServer.hpp"

int main(int ac, const char **av, char** environ) {
  if (ac != 2)
      av[1] = "conf/default.conf";
  try {
    WebServer  webserver(*(++av), environ);
    webserver.setServer();
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  return (0);
}
