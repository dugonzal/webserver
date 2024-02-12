# include "../inc/test.hpp"
    
void Test::Example() {
  Config config;


  std::string path = "../../conf/default.conf";
  config.parser = Parser(path);
  

  CPPUNIT_ASSERT_EQUAL((2 + 3), 5);
  }

