
# pragma once

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
# include "../../inc/server/config.hpp"

class Test : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(Test);
    CPPUNIT_TEST(Example);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp() {}
    void tearDown() {}
    void Example() ;


};

CPPUNIT_TEST_SUITE_REGISTRATION(Test);

