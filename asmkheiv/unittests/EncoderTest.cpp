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
  auto &L1 = AP.getTokens();
  EXPECT_EQ(L1[0], "addi") << "should be addi";
  EXPECT_EQ(L1[1], "a0") << "should be a0";
  EXPECT_EQ(L1[2], "a0") << "should be a0";
  EXPECT_EQ(L1[3], "2047") << "should be 2047";

  EXPECT_TRUE(AP.parseLine());

  auto &L2 = AP.getTokens();
  EXPECT_EQ(L2[0], "xori") << "should be xori";
  EXPECT_EQ(L2[1], "a1") << "should be a1";
  EXPECT_EQ(L2[2], "a2") << "should be a2";
  EXPECT_EQ(L2[3], "4") << "should be 4";
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