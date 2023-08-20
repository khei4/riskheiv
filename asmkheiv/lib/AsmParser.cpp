#include <AsmParser.h>
#include <iostream>


void stripWhiteSpace(std::string &s) {
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace),
        s.end());
}

void AsmParser::parseLineInner(const std::string &Line) {
  std::string Tok;
  std::stringstream local_ss(Line);
  assert((local_ss >> Tok) && "mnemonic can't be parsed!");
  stripWhiteSpace(Tok);

  if (auto II = ITypeKinds.find(Tok); II != ITypeKinds.end()) {
    const IType &ITyp = II->second;
    // TOOD: need more test
    unsigned imm= 777, rd = 777, rs1 = 777;
    assert(std::getline(local_ss, Tok, ',') && "rd can't be parsed!");
    stripWhiteSpace(Tok);
    std::cerr << "rd = "<< Tok << "\n";
    if (auto RI = GPRegs.find(Tok); RI != GPRegs.end())
      rd = RI->second;
    else assert(false && "invalid register name");
    std::cerr << "rd = "<< rd << "\n";
    assert(std::getline(local_ss, Tok, ',') && "rs1 can't be parsed!");
    stripWhiteSpace(Tok);
    std::cerr << "rs1 = "<< Tok << "\n";
    if (auto RI = GPRegs.find(Tok); RI != GPRegs.end())
      rs1 = RI->second;
    else assert(false && "invalid register name");
    std::cerr << "rs1 = "<< rs1 << "\n";
    assert(std::getline(local_ss, Tok, ',') && "imm can't be parsed!");
      imm = std::stoi(Tok);
    Inst = std::unique_ptr<ITypeInst>(new ITypeInst(imm, rd, rs1, ITyp));
  }else 
    assert(false && "Unimplemented!");
  

  // TODO: handle comment
  // while (std::getline(local_ss, temp, ',')) {
  //   std::stringstream item_ss(temp);
  //   std::string item;
  //     item_ss >> item;
  //     result.push_back(item);
  // }

}

bool AsmParser::parseLine() {
  std::string line;
  while (std::getline(Is, line)) {
    LineCounter++;
    if (line.find(':') != std::string::npos) continue;
    parseLineInner(line);
    return true;
  }
  return false;
}
