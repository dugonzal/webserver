/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/21 12:59:12 by jaizpuru         ###   ########.fr       */
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
  std::vector<string>::iterator ptrBegin = ptrData.begin();
  std::vector<string>::iterator ptrEnd = ptrData.end();
  for (ptrBegin = ptrData.begin(); (ptrBegin != ptrEnd); ptrBegin++) {
    std::cout << *ptrBegin << std::endl;
    if (ptrBegin->find("listen", 0) != std::string::npos) {
      if (servers.setPort(sCount, getHostFromLine(*ptrBegin), \
        getNumberFromLine(*ptrBegin)))
          throw(std::runtime_error("error: setPort failed, bad values."));
    }
    if (findStrInLog(*ptrBegin, "server_name") != "")
      servers.setName(findStrInLog(*ptrBegin, "server_name"));
    if (findStrInLog(*ptrBegin, "error_page") != "")
      servers.setErrorPage(findStrInLog(*ptrBegin, "error_page"));
    if (findStrInLog(*ptrBegin, "client_max_body_size") != "")
      servers.setClientBodySize(findStrInLog(*ptrBegin, "client_max_body_size"));
    if (!ptrBegin->compare("};")) {
      std::cout << std::endl;
      sCount++;
    }
  }
  std::cout << std::endl;
}
