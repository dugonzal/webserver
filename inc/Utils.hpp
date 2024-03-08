/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:34 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/07 06:38:08 by Dugonzal         ###   ########.fr       */
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
# include <list>

using std::list;
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
