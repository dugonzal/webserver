/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/20 16:12:08 by Dugonzal         ###   ########.fr       */
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
  servers.setServers(parser.getNservers());
  setServerConfig();
  servers.startServers();
}

void  Config::setServerConfig( void ) {
  int sCount = 0;
  std::vector<string> ptrData = parser.getData();

  for (unsigned int i = 0; i < ptrData.size(); i++) {
    // std::cout << ptrData[i] << std::endl;
    if (ptrData[i].find("listen", 0) != std::string::npos) {
      if (servers.setPort(sCount, getHostFromLine(ptrData[i]), \
        getNumberFromLine(ptrData[i])))
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
  }
  std::cout << std::endl;
}
