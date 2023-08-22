#include "BinaryEmitter.h"
#include <gtest/gtest.h>
#include <iostream>

// Demonstrate some basic assertions.
TEST(EncoderTest, ITypes) {
  auto ss = std::stringstream("addi x16, x0, 3\n"
                              "ori, x17, x16, 6\n");
  BinaryEmitter BE(ss);

  std::ostringstream OSS;
  BE.emitBinary(OSS);
  std::string Data = OSS.str();

  EXPECT_EQ(Data, "world");
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