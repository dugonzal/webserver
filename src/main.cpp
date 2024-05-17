/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:55:09 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/18 00:07:53 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/server/WebServer.hpp"

int main(int ac, const char **av) {
  if (ac != 2)
      av[1] = "conf/default.conf";
  try {
    if (checkProcess() == true)
      throw(runtime_error("error: webserver: already another process running"));
    WebServer  webserver(*(++av));
    webserver.setServer();
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  remove("checker");
  return (0);
}
