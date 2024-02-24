/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:56:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/24 13:20:42 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/test.hpp"

// usar rutas absolutas para los archivos de test
void  TestServer::openFile() {
  Parser parser;

  std::ifstream *file = parser.openFile("/home/ciclo/Documentos/42/webserver/conf/default.conf");
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

  config.parser = Parser("/home/ciclo/Documentos/42/webserver/conf/default.conf");
}

void TestServer::setUp() {}

void TestServer::tearDown() {}

void getNs() { }

