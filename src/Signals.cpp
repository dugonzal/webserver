/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:03:54 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/19 18:27:26 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Signals.hpp"

Signals::Signals(void) {
  signal(SIGINT, Signals::setSignals);
  signal(SIGQUIT, Signals::setSignals);
}

Signals::~Signals(void) { }

void Signals::setSignals(int sig) {
  cout  << endl << sig << "entra a sig" << endl;
  if (sig == SIGQUIT || sig == SIGINT) {
    for (vector<pollfd>::const_iterator it = fds.begin(); it != fds.end(); it++) {
      cout << "cerrando fd: " << it->fd << endl;
      close(it->fd);
    }
    exit(0);
  }
}
