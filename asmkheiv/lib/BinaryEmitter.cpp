#include "BinaryEmitter.h"
#include "Instructions.h"
#include "Registers.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <stdexcept>

std::pair<int, std::string> parseOffsetReg(const std::string &input) {
  std::string numStr, identifier;

  size_t i = 0;
  // 数字の部分を解析
  while (i < input.size() && (std::isdigit(input[i]) || input[i] == '-')) {
    numStr.push_back(input[i]);
    i++;
  }

  while (i < input.size() && (std::isalnum(input[i]) || input[i] == '_')) {
    identifier.push_back(input[i]);
    i++;
  }

  int num;
  try {
    num = std::stoi(numStr);
  } catch (const std::exception &e) {
    throw std::runtime_error("Failed to parse number from string.");
  }

  return {num, identifier};
}

void BinaryEmitter::emitBinary(std::ostream &os) {
  while (AP.parseLine()) {
    auto &Toks = AP.getTokens();
    auto &Mnemo = Toks[0];
    if (auto IT = ITypeKinds.find(Mnemo); IT != ITypeKinds.end()) {
      IType ITemp = IT->second;
      std::bitset<3> Funct3 = ITemp.getFunct3();
      std::bitset<7> Opcode = ITemp.getOpcode();

      std::bitset<5> Rd, Rs1;
      std::bitset<12> Imm;
      if (auto RI = GPRegs.find(Toks[1]); RI != GPRegs.end())
        Rd = RI->second;
      else
        assert(false && "invalid register name for rd");

      // handle offset for loads
      if (Toks.size() == 3) {
        assert((Mnemo == "lb" || Mnemo == "lh" || Mnemo == "lw" ||
                Mnemo == "lbu" || Mnemo == "lhu") &&
               "invarid offset(reg) except loads");
        auto OffReg = parseOffsetReg(Toks[2]);
        Rs1 = std::bitset<5>(OffReg.second);
        Imm = OffReg.first;
      } else {
        if (auto RI = GPRegs.find(Toks[2]); RI != GPRegs.end())
          Rs1 = RI->second;
        else
          assert(false && "invalid register name for rs1");
        Imm = stoi(Toks[3]);
      }

      unsigned Inst = (Imm.to_ulong() << 20) | (Rs1.to_ulong() << 15) |
                      (Funct3.to_ulong() << 12) | (Rd.to_ulong() << 7) |
                      Opcode.to_ulong();
      // unsigned Inst = (Opcode.to_ulong() << 27) | (Rs1.to_ulong() << 12) |
      //                 (Funct3.to_ulong() << 17) | (Rd.to_ulong() << 22) |
      //                 Imm.to_ulong();
      std::cout << Inst << '\n';
      std::cout << "Hex representation: 0x" << std::hex << std::uppercase
                << std::setw(8) << std::setfill('0') << Inst << std::endl;
      os.write(reinterpret_cast<char *>(&Inst), 4);
    } else {
      std::cerr << Mnemo << "\n";
      assert(false && "unimplemented!");
    }
  }
}