# include "../inc/test.hpp"

int main() {

  try {

    // Crea una suite de pruebas vacía
    CppUnit::TestSuite *suite = new CppUnit::TestSuite();
    // Agrega las pruebas de la clase TestExample a la suite de pruebas
    suite->addTest(new CppUnit::TestCaller<Test>("testSuma", &Test::Example));
    suite->addTest(new CppUnit::TestCaller<Test>("testSuma", &Test::Example));

    // Crea un corredor de pruebas de texto y ejecuta la suite de pruebas
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);
    bool wasSuccessful = runner.run();
    return wasSuccessful ? 0 : 1;
  }
    catch (std::exception &e) 
      {  std::cerr << "Error: " << e.what() << std::endl; }
    // Devuelve 0 si todas las pruebas fueron exitosas, 1 si hubo pruebas fallidas
}
