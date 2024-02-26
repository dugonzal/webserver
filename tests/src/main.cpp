/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:56:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/26 16:34:47 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/test.hpp"

int main() {
  try {
    // Crea una suite de pruebas vacía
    CppUnit::TestSuite *suite = new CppUnit::TestSuite();
    // Agrega las pruebas de la clase TestExample a la suite de pruebas
   suite->addTest(new CppUnit::TestCaller<TestServer>("parser", \
          &TestServer::parser));
    // Crea un corredor de pruebas de texto y ejecuta la suite de pruebas
    CppUnit::TextTestRunner runner;
    runner.addTest(suite);
    bool wasSuccessful = runner.run();
    return wasSuccessful ? 0 : 1;
  }
  catch (std::exception &e)
      {  std::cerr << "Error: " << e.what() << std::endl; }
}
