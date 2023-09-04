#include "BinaryEmitter.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

// https://github.com/d0iasm/rvemu/blob/07994c5261f69a130b6abcea70ba1ed0e2c9bbaf/tests/rv32i.rs#L11-L13
TEST(EncoderTest, ITypes) {
  auto ss = std::stringstream("addi, x16, x0, 5\n"
                              "addi, x17, x0, 3\n"
                              "slti x17, x16, -2\n"
                              "sltiu, x17, x16, 5 \n"
                              "xori, x17, x16, 6 \n"
                              "ori, x17, x16, 6\n"
                              "andi, x17, x16, 7\n"
                              "jalr x18, x0, 44\n"
                              "lb x18, 4(x0)\n"
                              "lh x18, 4(x0)\n"
                              "lbu x18, 4(x0)\n"
                              "lw x18, 4(x0)\n");

  BinaryEmitter BE(ss);

  std::ostringstream OSS;
  BE.emitBinary(OSS);
  std::string Bin = OSS.str();
  // better to be binary?
  int cnt = 0;
  // for (char c : Bin) {
  //   std::cerr << std::hex << std::setw(2) << std::setfill('0')
  //             << (0xff & static_cast<unsigned char>(c)) << ' ';
  //   ++cnt;
  //   if (cnt % 4 == 0)
  //     std::cerr << "\n";
  // }
  unsigned char Expected[] = {
      0x13, 0x08, 0x50, 0x00, // addi, x16, x0, 5
      0x93, 0x08, 0x30, 0x00, // addi, x17, x0, 3
      0x93, 0x28, 0xe8, 0xff, // slti x17, x16, -2
      0x93, 0x38, 0x58, 0x00, // sltiu, x17, x16, 5
      0x93, 0x48, 0x68, 0x00, // xori, x17, x16, 6
      0x93, 0x68, 0x68, 0x00, // ori, x17, x16, 6
      0x93, 0x78, 0x78, 0x00, // andi, x17, x16, 7
      0x67, 0x09, 0xc0, 0x02, // jalr x18, x0, 44
      0x03, 0x09, 0x40, 0x00, // lb x18, 4(x0)
      0x03, 0x19, 0x40, 0x00, // lh x18, 4(x0)
      0x03, 0x49, 0x40, 0x00, // lbu x18, 4(x0)   TODO: suspicious.
      0x03, 0x29, 0x40, 0x00, // lw x18, 4(x0)
  };

  EXPECT_EQ(std::memcmp(Bin.data(), Expected, sizeof(Expected)), 0);
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