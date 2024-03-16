/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:08 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 08:44:58 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Utils.hpp"

bool  skipLine(const string &line) {
  if (line.empty() || line[0] == '#')
      return(true);
  return(false);
}
string trim(const string &line) {
  std::size_t first = line.find_first_not_of(" \t\v\f\r");

  if (first == string::npos)
    return ("");

  std::size_t last = line.find_last_not_of(" \t\v\f\r");

  return (line.substr(first, ((last - first) + 1)));
}

string  cleanSemiColon(string tmp) {
  if (tmp[tmp.size() - 1] == ';')
    tmp[tmp.size() - 1] = '\0';
  return (tmp);
}
