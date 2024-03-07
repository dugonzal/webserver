/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/07 19:00:19 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Config.hpp"

Config::Config(void) { }

Config::~Config(void) { }

Config::Config(const string &filename): parser(filename) {
  setServers();
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

void  Config::setServers(void) {
  // Prints the configuration parsed data
  // parser.printData(parser.getData());

  servers.setServers(parser.getNservers());
  setWorkerConnections();
}

void  Config::setWorkerConnections( void ) {
  int i = 0;
  int sCount = 1;
  std::vector<string> ptrData = parser.getData();
  std::vector<string>::iterator ptrBegin = ptrData.begin();
  std::vector<string>::iterator ptrEnd = ptrData.end();
  for (ptrBegin = ptrData.begin(); (ptrBegin != ptrEnd); ptrBegin++) {
    if (ptrData[i].find("worker_connections", 0) != std::string::npos)
      servers.setWorkerConnections(getNumberFromLine(ptrData[i]));
    if (ptrData[i].find("listen", 0) != std::string::npos) {
      if (servers.setPort(sCount, getNumberFromLine(ptrData[i])))
        throw(std::runtime_error("error: setPort failed, bad values."));
    }
    if (findStrInLog(ptrData[i], "server_name") != "")
      servers.setName(sCount++, findStrInLog(ptrData[i], "server_name"));
    i++;
  }
}
