#ifndef ENCODER_H
#define ENCODER_H
#include "AsmParser.h"
#include <bitset>
#include <map>
#include <string>

class Encoder {

private:
  using Address = unsigned;
  Address PC;
  std::map<std::string, Address> Labels;

  /// create label map
  void readLabels(AsmParser &);

public:
  Encoder(const Encoder &) = delete;
  Encoder &operator=(const Encoder &) = delete;

  Encoder() : PC(0) {}

  /// Encode asm into baremetal binary
  bool encode(AsmParser &);
};

#endif