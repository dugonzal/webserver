/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:46:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 14:28:09 by Dugonzal         ###   ########.fr       */
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

void  Logger::Log(const char *line, ...) {
  time_t t = time(0);
  char *c_time = ctime_r(&t, new char[500]);
  char out[1024] = {0};
  va_list arg;

  va_start(arg, line);

  if (!file.is_open()) {
    cerr << "file logger no open" << endl;
    return;
  }

  c_time[strlen(c_time) - 1] = 0;
  vsnprintf(out, sizeof(out), line, arg);
  cout << WHT << "[INFO] " << END << c_time \
    << " | " << BLU << out << END << endl;

  file << "[INFO] " << c_time << " | " << out << endl;

  va_end(arg);
  delete [] c_time;
}
