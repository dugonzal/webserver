/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:36:45 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 14:23:08 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Config.hpp"

Config::Config(void) { }

Config::~Config(void) { }

Config::Config(const string &filename): parser(filename) {
  servers = parser;
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
