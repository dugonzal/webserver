/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:46:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 13:19:00 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Logger.hpp"

Logger::Logger(void): file("server.log", ios::out | ios::app) { }

Logger::Logger(const string &name): file(name.data(), ios::out | ios::app) { }

Logger::~Logger(void) { file.close(); }

Logger::Logger(const Logger &copy) {
  if (this != &copy) {
    fileName = copy.fileName;
  }
}

Logger &Logger::operator=(const Logger &copy) {
  if (this != &copy) {
    fileName = copy.fileName;
  }
  return(*this);
}

/*
void Logger::Log(const char *line, ...) {
  cout << YEL  << log << END << endl;
}
*/
