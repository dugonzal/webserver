# pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>
# include "suma.hpp"

class MyTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(MyTest);
    CPPUNIT_TEST(testExample);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() {}
    void tearDown() {}

    void testExample() {
        CPPUNIT_ASSERT_EQUAL(suma(2, 2), 4);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MyTest);

