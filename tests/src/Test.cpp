/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:56:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/13 01:34:29 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/test.hpp"
#include <cppunit/TestAssert.h>

void TestServer::setUp() {}
    
void TestServer::tearDown() {}
    
void TestServer::Example() {
  Server server;

  std::cout << "TestServer::Example" << std::endl;
  std::cout << server << std::endl;
  CPPUNIT_ASSERT(server.setBind() == true);
}

