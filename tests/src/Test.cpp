/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:56:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/24 11:10:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/test.hpp"

void TestServer::setUp() {}

void TestServer::tearDown() {}

void TestServer::bind() {
  Server server;

  std::cout << "TestServer::Example" << std::endl;
  std::cout << server << std::endl;
  CPPUNIT_ASSERT(true == true);
}

void getNs() { }

