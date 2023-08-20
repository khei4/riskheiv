#include "AsmParser.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(EncoderTest, Basics) {
  auto ss = std::stringstream("addi a0, a0, 2047\n"
                              "xori a1, a2, 4\n");
  AsmParser AP(ss);

  EXPECT_EQ(0, AP.getLineCounter());
  EXPECT_TRUE(AP.parseLine());

  EXPECT_EQ(1, AP.getLineCounter());
}

TEST(EncoderTest, Labels) {
  auto ss = std::stringstream("addi a0, a0, 2047\n"
                              "xori a0, a0, 4\n");
  AsmParser AP(ss);
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}