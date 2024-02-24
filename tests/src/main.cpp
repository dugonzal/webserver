/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:56:36 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/24 11:34:41 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/test.hpp"

int main() {
  try {
    // Crea una suite de pruebas vacía
    CppUnit::TestSuite *suite = new CppUnit::TestSuite();
    // Agrega las pruebas de la clase TestExample a la suite de pruebas
    suite->addTest(new CppUnit::TestCaller<TestServer>("examplet", \
          &TestServer::example));

    // Crea un corredor de pruebas de texto y ejecuta la suite de pruebas
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);
    bool wasSuccessful = runner.run();
    return wasSuccessful ? 0 : 1;
  }
  catch (std::exception &e)
      {  std::cerr << "Error: " << e.what() << std::endl; }
}
