#include <gtest/gtest.h>

class Foo {
public:
  unsigned int factorial( unsigned int number ) {
      return number <= 1 ? number : factorial(number-1)*number;
  }
};

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class FooTestMain : public ::testing::Test {
protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  FooTestMain() {
     // You can do set-up work for each test here.
  }

  ~FooTestMain() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Foo::factorial() method does Abc.
TEST_F(FooTestMain, MethodFactorialDoesAbc) {
  Foo f;
  EXPECT_EQ(f.factorial(1),  1);
  EXPECT_EQ(f.factorial(2),  2);
  EXPECT_EQ(f.factorial(3),  6);
  EXPECT_EQ(f.factorial(10), 3628800);
}

// Tests that Foo does Xyz.
TEST_F(FooTestMain, DoesXyz) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
