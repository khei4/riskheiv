#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class AsmParser {
private:
  std::istream &Is;
  std::vector<std::string> Toks;
  int LineCounter;

  // TODO: handle jump labels
  // define on AsmParser.cpp
  std::vector<std::string> parseLineInner(const std::string &str);

public:
  AsmParser(std::istream &is) : Is(is), LineCounter(0) {}

  /// read line
  bool parseLine();
  const std::vector<std::string> &getTokens() { return Toks; }

  int getLineCounter() const { return LineCounter; }
};
