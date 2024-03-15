/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/15 17:21:13 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Config.hpp"

Config::Config(void) { }

Config::~Config(void) { }

Config::Config(const string &filename): parser(filename) {
  setServer();
}

Config::Config(const Config &copy): \
  servers(copy.servers), parser(copy.parser), signals(copy.signals) { }

Config &Config::operator=(const Config &copy) {
  if (this != &copy) {
    servers = copy.servers;
    parser = copy.parser;
    signals = copy.signals;
  }
  return (*this);
}

void  Config::setServer(void) {
  // Prints the configuration parsed data
  // parser.printData(parser.getData());

  servers.setServers(parser.getNservers() - 1); // manually set -1, remove ASAP
  setServerConfig();
  servers.startServers();
}

void  Config::setServerConfig( void ) {
  int i = 0;
  int sCount = 1;
  std::vector<string> ptrData = parser.getData();
  std::vector<string>::iterator ptrBegin = ptrData.begin();
  std::vector<string>::iterator ptrEnd = ptrData.end();
  for (ptrBegin = ptrData.begin(); (ptrBegin != ptrEnd); ptrBegin++) {
    // std::cout << ptrData[i] << std::endl;
    if (ptrData[i].find("listen", 0) != std::string::npos) {
      if (servers.setPort(sCount, getHostFromLine(ptrData[i]), getNumberFromLine(ptrData[i])))
        throw(std::runtime_error("error: setPort failed, bad values."));
      
    }
    if (findStrInLog(ptrData[i], "server_name") != "")
      servers.setName(findStrInLog(ptrData[i], "server_name"));
    if (findStrInLog(ptrData[i], "error_page") != "")
      servers.setErrorPage(findStrInLog(ptrData[i], "error_page"));
    if (findStrInLog(ptrData[i], "client_max_body_size") != "")
      servers.setClientBodySize(findStrInLog(ptrData[i], "client_max_body_size"));
    if (!ptrData[i].compare("};")) {
      std::cout << std::endl;
      sCount++;
    }
    i++;
  }
  std::cout << std::endl;
}
