#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <bitset>
#include <map>
class IType {
private:
  const std::string mnemonic;
  const std::bitset<3> funct3;
  const std::bitset<7> opcode;

public:
  IType(const std::string &mnemonic, const unsigned funct3,
        const unsigned opcode)
      : mnemonic(mnemonic), funct3(funct3), opcode(opcode) {}
  const std::string &getMnemonic() const { return mnemonic; }
  const std::bitset<3> &getFunct3() const { return funct3; }
  const std::bitset<7> &getOpcode() const { return opcode; }
};

const std::map<std::string, IType> ITypeKinds = {
    {"addi", {"addi", 0b000, 0b0010011}},
    {"slti", {"slti", 0b010, 0b0010011}},
    {"sltiu", {"sltiu", 0b011, 0b0010011}},
    {"xori", {"xori", 0b100, 0b0010011}},
    {"ori", {"ori", 0b110, 0b0010011}},
    {"andi", {"andi", 0b111, 0b0010011}},
    {"jalr", {"jalr", 0b000, 0b1100111}},
    {"lb", {"lb", 0b000, 0b0000011}},
    {"lh", {"lh", 0b001, 0b0000011}},
    {"lw", {"lw", 0b010, 0b0000011}},
    {"lbu", {"lbu", 0b100, 0b0000011}},
    {"lhu", {"lhu", 0b101, 0b0000011}}};

#endif