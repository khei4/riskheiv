#ifndef ASMPARSER_H
#define ASMPARSER_H

#include "Instructions.h"
#include "Registers.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

class AsmParser {
private:
  using Address = unsigned;

  std::istream &Is;
  std::unique_ptr<RV32Inst> Inst;
  int LineCounter;
  Address PC;
  std::map<std::string, Address> Labels;

  // TODO: handle jump labels
  // define on AsmParser.cpp
  void parseLineInner(const std::string &str);

public:
  AsmParser(const AsmParser &) = delete;
  AsmParser &operator=(const AsmParser &) = delete;
  AsmParser(std::istream &is) : Is(is), LineCounter(0), PC(0) {
    // initialize Labels
    std::string line;
    while (std::getline(Is, line)) {
      if (line.find(':') != std::string::npos) {
        Labels.insert({line.substr(0, line.find(':')), PC});
        continue;
      }
      PC += 4;
    }
    Is.clear();
    Is.seekg(0, std::ios::beg);
    PC = 0;
  }

  /// read line
  bool parseLine();

  std::unique_ptr<RV32Inst> moveInst() { return std::move(Inst); }

  int getLineCounter() const { return LineCounter; }
};
#endif