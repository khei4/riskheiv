#include <AsmParser.h>
#include <Encoder.h>
#include <cassert>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>"
              << "\n";
    return 1;
  }
  // const std::string filename = argv[1];
  // auto Files = std::ifstream(filename);
  // AsmParser parser(Files);

  // std::vector<std::string> labels = {"mnemonic", "op0", "op1", "op2",
  //                                    "comment"};
  // while (parser.parseLine()) {
  //   std::cout << "Line " << parser.getLineCounter() << ": ";
  //   const auto &tokens = parser.getTokens();
  //   int cnt = 0;
  //   for (const std::string &token : tokens) {
  //     if (token.find(":") != std::string::npos) {
  //       std::cout << "label: " << token;
  //     } else {
  //       std::cout << labels[cnt] << ": " << token << ", ";
  //       ++cnt;
  //     }
  //   }
  //   std::cout << "\n";
  // }

  // parser.seek0();

  // while (parser.parseLine()) {
  //   std::cout << "Line " << parser.getLineCounter() << ": ";
  //   const auto &tokens = parser.getTokens();
  //   int cnt = 0;
  //   for (const std::string &token : tokens) {
  //     if (token.find(":") != std::string::npos) {
  //       std::cout << "label: " << token;
  //     } else {
  //       std::cout << labels[cnt] << ": " << token << ", ";
  //       ++cnt;
  //     }
  //   }
  //   std::cout << "\n";
  // }

  // return 0;
  // // Encode("hogehoge");
  // return 0;
}
