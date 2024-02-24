/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:08 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/24 10:36:35 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/utils.hpp"

std::string trim(const std::string &line) {
  std::size_t first = line.find_first_not_of(" \t\v\f\r");

  if (first == std::string::npos)
    return ("");

  std::size_t last = line.find_last_not_of(" \t\v\f\r");

  return (line.substr(first, ((last - first) + 1)));
}

