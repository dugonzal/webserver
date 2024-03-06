/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:08 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/06 16:26:54 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Utils.hpp"

bool  skipLine(const string &line) {
  /* If line is empty OR a comment is made */
  if (line.empty() || line[0] == '#')
      return(true);
  return(false);
}
string trim(const string &line) {
  /* Finds the first character that is not (space, tab, ...) */
  std::size_t first = line.find_first_not_of(" \t\v\f\r");

  /* Checks that the first character is not the end of file */
  if (first == string::npos)
    return ("");

  /* Finds the last character that is not (space, tab, ...) */
  std::size_t last = line.find_last_not_of(" \t\v\f\r");

  /* Returns the resulting lines between first & last */
  return (line.substr(first, ((last - first) + 1)));
}
