/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:46:12 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 22:28:55 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Logger.hpp"

Logger::Logger(void): file("logs/serverLog.log", ios::out | ios::app) { }

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

  if (!file.is_open()) {
    delete [] c_time;
    cerr << "file logger no open" << endl;
    return;
  }

  va_start(arg, line);
  c_time[strlen(c_time) - 1] = 0;
  vsnprintf(out, sizeof(out), line, arg);
  cout << MAG << "[INFO] " << END << c_time \
    << " | " << BLU << out << END << endl;

  file << "[INFO] " << c_time << " | " << out << endl;

  va_end(arg);
  delete [] c_time;
}
