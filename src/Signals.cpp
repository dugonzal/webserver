/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:03:54 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 10:34:51 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Signals.hpp"

Signals::Signals(void) {
  signal(SIGINT, Signals::setSignals);
  signal(SIGQUIT, Signals::setSignals);
}

Signals::~Signals(void) { }

void Signals::setSignals(int sig) {
  cout << endl;
  if (sig == SIGQUIT || sig == SIGINT) {
    for (vector<pollfd>::const_iterator it = fds.begin(); \
      it != fds.end(); it++) {
        cout << RED << "close fd: " << it->fd << END << endl;
        close(it->fd);
    }
    cout << CYN << "Server conquered! Keep coding, stay safe. 🙂🙂🙂" << END << endl;
    exit(0);
  }
}
