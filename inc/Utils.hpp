/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:34 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/20 13:58:08 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# define BLK "\033[0;30m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYN "\033[0;36m"
# define WHT "\033[0;37m"
# define END "\033[0m\n"
# define WHITESPACES " \t\n\r\v"

# include <sys/un.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/poll.h>
# include <stdexcept>
# include <map>
# include <list>
# include <csignal>
# include <string>
# include <iostream>
# include <ostream>
# include <vector>
# include <deque>
# include <fstream>
# include <cstdlib>
# include <cstddef>
# include <set>
# include <cassert>
# include <sstream>
//# include <chrono>
//# include <thread>
# include "Signals.hpp"

extern std::vector<pollfd> fds;

using std::deque;
using std::set;
using std::cout;
using std::endl;
using std::string;
using std::runtime_error;
using std::logic_error;
using std::exception;
using std::ifstream;
using std::vector;
using std::size_t;
using std::map;
using std::list;
using std::ostream;
using std::make_pair;
using std::pair;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::cerr;
bool    errorFile(ifstream);
string  trim(const string&);
bool    skipLine(const string&);
string  readFile(const string& filename);
string  firstWord(string line);
string  lastWord(string line);
size_t  numberWords(const string  &line);
