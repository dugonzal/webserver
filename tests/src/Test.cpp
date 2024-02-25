/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:56:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/25 21:32:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/test.hpp"

// usar rutas absolutas para los archivos de test
void  TestServer::openFile() {
  Parser parser;
  string  filename = "/home/ciclo/Documentos/42/webserver/conf/default.conf";

  std::ifstream *file = parser.openFile(filename);
  try {
    CPPUNIT_ASSERT(file->is_open());
    delete file;
  } catch (std::exception &e) {
    delete file;
    CPPUNIT_ASSERT(false);
  }
}

void TestServer::parser() {
  Config  config;
  string  filename;

  filename = "/home/ciclo/Documentos/42/webserver/conf/default.conf";
  config.parser = Parser(filename);
  CPPUNIT_ASSERT(config.parser.getNservers());
}

void TestServer::setUp() {}

void TestServer::tearDown() {}

void getNs() { }

