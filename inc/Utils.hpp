/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:34 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/14 11:16:07 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <sys/un.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdexcept>
# include <map>
# include <string>
# include <iostream>
# include <ostream>
# include <vector>
# include <fstream>
# include <cstdlib>
# include <cstddef>
# include <cassert>
# include <sstream>
# include <fcntl.h>
# include <sys/ioctl.h>

using std::cout;
using std::endl;
using std::string;
using std::runtime_error;
using std::logic_error;
using std::ifstream;
using std::vector;
using std::size_t;
using std::map;
using std::ostream;

bool    errorFile(ifstream);
string  trim(const string&);
bool    skipLine(const string&);
int  getNumberFromLine( const std::string& line );
std::string	getNameFromLine( const std::string& line, const std::string& strBefore );
std::string  findStrInLog( const std::string& line, const std::string& toFind );
std::string readFaviconFile(const std::string& filename);
