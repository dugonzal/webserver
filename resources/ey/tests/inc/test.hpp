/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:56:31 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/22 09:01:17 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
# include "../../inc/server/WebServer.hpp"
# include "../../inc/parser/Parser.hpp"

class TestServer : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestServer);
    CPPUNIT_TEST(openFile); // Agrega una prueba llamada Example
    CPPUNIT_TEST(parser); // Agrega una prueba llamada Example
    CPPUNIT_TEST_SUITE_END();
 public:
    void setUp();
    void tearDown();
    void openFile();
    void parser();

CPPUNIT_TEST_SUITE_REGISTRATION(TestServer);
// registro de la suite de pruebas
};
