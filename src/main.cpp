/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/06/02 21:15:43 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server/WebServer.hpp"

int main(int ac, const char **av) {
  if (ac not_eq 2)
      av[1] = "conf/default.conf";
  try {
    WebServer  webserver(*(++av));

    webserver.setServer();
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  return (0);
}
