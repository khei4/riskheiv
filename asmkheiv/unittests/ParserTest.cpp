#include "AsmParser.h"
#include "Support.h"
#include <gtest/gtest.h>
#include <iostream>

template std::unique_ptr<ITypeInst>
dynamic_unique_cast<ITypeInst, RV32Inst>(std::unique_ptr<RV32Inst> &&);

// Demonstrate some basic assertions.
TEST(ParserTest, Basics) {
  auto ss = std::stringstream("addi a0, a0, 2047\n"
                              "xori a1, a2, 4\n");
  AsmParser AP(ss);

  EXPECT_EQ(0, AP.getLineCounter());

  EXPECT_TRUE(AP.parseLine());
  std::unique_ptr<ITypeInst> Addi =
      dynamic_unique_cast<ITypeInst, RV32Inst>(AP.moveInst());

  EXPECT_EQ(1, AP.getLineCounter());
  EXPECT_EQ(Addi->getMnemonic(), "addi");
  EXPECT_EQ(Addi->getFunct3(), 0b000);
  EXPECT_EQ(Addi->getOpcode(), 0b0010011);
  EXPECT_EQ(Addi->getImm(), 2047);
  EXPECT_EQ(Addi->getRD(), 10);
  EXPECT_EQ(Addi->getRS1(), 10);

  EXPECT_TRUE(AP.parseLine());

  std::unique_ptr<ITypeInst> Xori =
      dynamic_unique_cast<ITypeInst, RV32Inst>(AP.moveInst());

  EXPECT_EQ(2, AP.getLineCounter());
  EXPECT_EQ(Xori->getMnemonic(), "xori");
  EXPECT_EQ(Xori->getFunct3(), 0b100);
  EXPECT_EQ(Xori->getOpcode(), 0b0010011);
  EXPECT_EQ(Xori->getImm(), 4);
  EXPECT_EQ(Xori->getRD(), 11);
  EXPECT_EQ(Xori->getRS1(), 12);
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