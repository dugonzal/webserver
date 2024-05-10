/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:03:54 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/11 00:55:38 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Signals.hpp"

Signals::Signals(void) {
  signal(SIGINT, Signals::setSignals);
  signal(SIGQUIT, Signals::setSignals);
}

Signals::~Signals(void) { }

void Signals::setSignals(int sig) {
  Logger logger;

  cout << endl;
  if (sig == SIGQUIT || sig == SIGINT) {
    for (vector<pollfd>::const_iterator it = fds.begin(); \
      it != fds.end(); it++) {
        logger.Log("close fd [%d]", it->fd);
        close(it->fd);
    }
    logger.Log("Server conquered! Keep coding, stay safe. 🙂🙂🙂");
    flag = false;
  }
}
