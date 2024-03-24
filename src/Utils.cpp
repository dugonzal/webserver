/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:08 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/24 17:03:35 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Utils.hpp"

bool  skipLine(const string &line) {
  if (line.empty() || line[0] == '#')
      return(true);
  return(false);
}

string trim(const string &line) {
  size_t first = line.find_first_not_of(" \t\v\f\r");

  if (first == string::npos)
    return ("");

  size_t last = line.find_last_not_of(" \t\v\f\r");

  return (line.substr(first, ((last - first) + 1)));
}

int getNumberFromLine(const string& line) {
  char c = 0;
  int flag = 0;
  std::stringstream ss;
  std::string::const_iterator itBegin = line.begin();
  std::string::const_iterator itEnd = line.end();

  if (line.find(':', 0) != std::string::npos)
    flag = 1;
  else
    flag = 2;
  for (; itBegin != itEnd; ++itBegin) {
    if (flag == 1) {
      if (*itBegin == ':')
        break;
    }
    else if (flag == 2) {
      if (std::isspace(*itBegin))
        break;
    }
  }

  for (; itBegin != itEnd; ++itBegin) {
    c = *itBegin;
    if (std::isdigit(c) || c == '.')
      ss << c;
    else if(c == '#' || c == ';')
      break;
  }
  int ret = 80;
  if (line.find("default_server", 0) != std::string::npos)
    std::cout << "warning: port: (default_server) directive was set" << std::endl;
  else if (ss.str().empty())
    std::cout << "warning: Port was not set, default set to 80" << std::endl;
  else
    ss >> ret;
  return ret;
}

std::string	getNameFromLine( const std::string& line, const std::string& strBefore ) {
  char c = 0;
  std::stringstream ss;
  std::string::const_iterator itBegin = line.begin();
  std::string::const_iterator itEnd = line.end();
  for (; itBegin != itEnd; ++itBegin) {
    c = *itBegin;
    ss << c;
    if (!ss.str().compare(strBefore)) {
      itBegin++;
      break;
    }
    else if(c == '#' || c == ';')
      break;
  }
  for (; itBegin != itEnd; ++itBegin) {
    c = *itBegin;
    if (c != ' ')
      break;
  }
  std::stringstream ret;
  ss.clear();
  for (; itBegin != itEnd; ++itBegin) {
    c = *itBegin;
    if(c == '#' || c == ';')
      break;
    else if (std::isalpha(c) || c == '_')
      ret << c;
  }
  if (ss.str().empty())
    std::cout << "warning: Name was not set" << std::endl;
  return ret.str();
}

std::string  findStrInLog( const std::string& line, const std::string& toFind ) {
  std::stringstream ss;
  char c = 0;
  bool exitLoop = false;
  std::string::const_iterator itBegin = line.begin();
  std::string::const_iterator itBegin2;
  std::string::const_iterator itEnd = line.end();
  for (; itBegin != itEnd && !exitLoop; itBegin++) { // skip spaces & get after toFind
    if (*itBegin != ' ') {
        itBegin2 = itBegin;
        for (; itBegin2 != itEnd; itBegin2++) {
          c = *itBegin2;
          if ((std::isalnum(c) || c == '_') && c != ';' && c != '#') {
            ss << c;
            if (!ss.str().compare(toFind)) {
              itBegin2++;
              exitLoop = true;
              break;
            }
          }
          else
            return "";
        }
    }
  }
  int len = 0;
  std::stringstream ret;
  for (; itBegin2 != itEnd; itBegin2++) {
    c = *itBegin2;
    if (c != ' ' && !std::isspace(c)) {
      if (c == ';' || c == '#') {
        if (!len)
          return ("");
        else
          break;
      }
      ret << c;
      len++;
    }
  }
  return ret.str();
}

// Function to read the contents of the favicon.ico file
std::string readFile(const std::string& filename) {
    std::ifstream file(filename.data(), std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

std::string  getHostFromLine( const std::string& line ) {
  char c = 0;
  int flag = 0;
  std::string ret;
  std::stringstream ss;
  std::string::const_iterator itBegin = line.begin();
  std::string::const_iterator itEnd = line.end();

  if (line.find(':', 0) != std::string::npos)
    flag = 1;
  else
    flag = 2;
  for (; itBegin != itEnd; ++itBegin) {
    if (flag == 1) {
      if (isspace(*itBegin))
        break;
    }
    else if (flag == 2)
      return ("0.0.0.0");
  }

  for (; itBegin != itEnd; ++itBegin) {
    c = *itBegin;
    if (std::isalpha(c) || std::isalnum(c) || c == '.')
      ss << c;
    else if(c == '#' || c == ';' || c == ':')
      break;
  }
  if (ss.str().empty()) {
    std::cout << "warning: Host was not set, default set to 0.0.0.0" << std::endl;
    return ("0.0.0.0");
  }
  else if (!ss.str().compare("defaultserver") || !ss.str().compare("localhost"))
    return ("0.0.0.0");
  else
    ss >> ret;
  return ret;
}
