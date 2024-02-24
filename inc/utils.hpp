/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:34 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/24 10:42:02 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma  once

# include <sys/un.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
#include <stdexcept>
# include <map>
# include <string>
# include <iostream>
# include <vector>
# include <fstream>
# include <cstdlib>
# include <cassert>

using std::cout;
using std::endl;
using std::string;
using std::runtime_error;
using std::logic_error;
using std::ifstream;

bool  errorFile(std::ifstream);

std::string trim(const std::string &);
