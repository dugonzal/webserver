/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:34 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/02 18:32:07 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <exception>
#define RED "\033[1;31m"
#define END "\033[0m\n"

# include <sys/un.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <stdexcept>
# include <map>
# include <list>
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
using std::ostream;

bool    errorFile(ifstream);
string  trim(const string&);
bool    skipLine(const string&);
int     getNumberFromLine(const string& line);
string  getNameFromLine(const string& line, const string& strBefore);
string  findStrInLog(const string& line, const string& toFind);
string  readFile(const string& filename);
string  getHostFromLine(const string& line);
string  firstWord(string line);
string  lastWord(string line);
