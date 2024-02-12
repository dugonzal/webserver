# include "../inc/test.hpp"


int main() {
    CppUnit::TestResult testResult;

    CppUnit::TestResultCollector resultCollector;
    testResult.addListener(&resultCollector);

    CppUnit::TextOutputter textOutputter(&resultCollector, std::cout);
    textOutputter.write();

    CppUnit::TestRunner testRunner;
    testRunner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    testRunner.run(testResult);

    return resultCollector.wasSuccessful() ? 0 : 1;
}

