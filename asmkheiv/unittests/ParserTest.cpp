#include "AsmParser.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(ParserTest, Basics) {
  auto ss = std::stringstream("addi a0, a0, 2047\n"
                              "xori a0, a0, 4\n");
  AsmParser AP(ss);

  EXPECT_EQ(0, AP.getLineCounter());
  EXPECT_TRUE(AP.parseLine());

  const auto &Toks = AP.getTokens();
  EXPECT_EQ(Toks[0], "addi") << "should addi";
  EXPECT_EQ(Toks[1], "a0") << "should a0";
  EXPECT_EQ(Toks[2], "a0") << "should a0";
  EXPECT_EQ(Toks[3], "2047") << "should 2047";
}

TEST(ParserTest, Labels) {
  auto ss = std::stringstream("addi a0, a0, 2047\n"
                              "xori a0, a0, 4\n");
  AsmParser AP(ss);
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}