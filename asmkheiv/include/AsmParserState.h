#include <string>
#include <vector>

enum CommentMode { In, Out};
class AsmState {
  public:
  std::string Line;
  std::vector<std::string> Buf;
  FILE *Fp;
  unsigned PcInterval;
  unsigned LineNo;
  unsigned pc;
  CommentMode CM;
};