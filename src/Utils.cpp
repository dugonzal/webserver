/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:08 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/13 19:41:24 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Utils.hpp"

bool  skipLine(const string &line) {
  if (line.empty() || line[0] == '#')
      return(true);
  return(false);
}

string  firstWord(string line) {
  size_t pos = line.find_first_of(WHITESPACES);

  if (pos == string::npos)
    return (line);

  return (line.substr(0, pos));
}

string  lastWord(string line) {
  size_t pos = line.find_first_of(WHITESPACES);

  if (pos == string::npos)
    return ("");

  return (trim(line.substr(pos)));
}

string trim(const string &line) {
  size_t first = line.find_first_not_of(WHITESPACES);

  if (first == string::npos)
    return ("");

  size_t last = line.find_last_not_of(WHITESPACES);

  return (line.substr(first, ((last - first) + 1)));
}

bool isW(const char c) {
  for (size_t i = 0; i < strlen(WHITESPACES) ; i++)
    if (WHITESPACES[i] == c)
    return (true);
  return (false);
}

size_t  numberWords(const string  &line) {
  size_t  count = 0, i = 0;

  while (i < line.size()) {
    if (!isW(line[i])) {
      count++;
      while (i < line.size() && !isW(line[i]))
        i++;
    }
    i++;
  }
  return (count);
}

string readFile(const std::string& filename) {
    ifstream file(filename.data(), std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}
