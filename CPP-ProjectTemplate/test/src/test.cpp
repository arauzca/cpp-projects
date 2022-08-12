#include <gtest/gtest.h>
#include <project_template.hpp>

unsigned int factorial( unsigned int number ) {
    return number <= 1 ? number : factorial(number-1)*number;
}

// Tests that the factorial() function does Abc.
TEST(FooTest, FunctionFactorialDoesAbc) {
  EXPECT_EQ(factorial(1),  1);
  EXPECT_EQ(factorial(2),  2);
  EXPECT_EQ(factorial(3),  6);
  EXPECT_EQ(factorial(10), 3628800);
}

TEST(ProjectTemplateTest, FunctionGetStringRetursTheString) {
  ProjectTemplate p1("Hello World");
  EXPECT_EQ(p1.getString(), "Hello World");
  
  ProjectTemplate *p2 = new ProjectTemplate("Testing ProjectTemplate");
  EXPECT_EQ(p2->getString(), "Testing ProjectTemplate");
}
