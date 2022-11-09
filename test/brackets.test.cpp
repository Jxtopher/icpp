#define ClassTest Brackets_test

#include "brackets.hpp"

#include "test.h"

using namespace icpp;

class ClassTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ClassTest);
    CPPUNIT_TEST(create);
    CPPUNIT_TEST_SUITE_END();

 protected:
    void create() {
        Brackets brackets;
        CPPUNIT_ASSERT(brackets.is_closed());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ClassTest);