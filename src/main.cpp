/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/18 12:12:28 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server/WebServer.hpp"

int main(int ac, const char **av) {
  if (ac != 2)
      av[1] = "conf/default.conf";
  try {
    WebServer  webserver(*(++av));
    webserver.setServer();
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  return (0);
}
