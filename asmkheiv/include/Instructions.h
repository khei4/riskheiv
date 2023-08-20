#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <bitset>
#include <map>
// TODO:
// 命令は一番上の親のクラスでもう持っておいて、それを操作する形でメソッドを追加する
class RV32Inst {
private:
  const std::string mnemonic;
  const std::bitset<7> opcode;

public:
  virtual ~RV32Inst() = default;
  RV32Inst(const std::string &mnemonic, const unsigned opcode)
      : mnemonic(mnemonic), opcode(opcode) {}
  const std::string &getMnemonic() const { return mnemonic; }
  const std::bitset<7> &getOpcode() const { return opcode; }
};

class IType : public RV32Inst {
private:
  const std::bitset<3> funct3;

public:
  IType(const std::string &mnemonic, const unsigned funct3,
        const unsigned opcode)
      : RV32Inst(mnemonic, opcode), funct3(funct3) {}
  const std::bitset<3> &getFunct3() const { return funct3; }
};

class ITypeInst : public IType {
private:
  const std::string mnemonic;
  const std::bitset<12> imm;
  const std::bitset<5> rd, rs1;

public:
  ITypeInst(const unsigned imm, const unsigned rd, const unsigned rs1,
            const IType &Ty)
      : IType(Ty), imm(imm), rd(rd), rs1(rs1) {}

  const std::bitset<12> &getImm() const { return imm; }
  const std::bitset<5> &getRD() const { return rd; }
  const std::bitset<5> &getRS1() const { return rd; }
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