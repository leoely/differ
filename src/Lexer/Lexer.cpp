#include <string>
#include <list>

using std::list;
using std::string;

class Lexer {
  protected:
    string value;
    int line, position;
    list<char> chars;
  public:
    Lexer();
    ~Lexer();
    const string& getValue();
};

Lexer::Lexer() : line(0), position(0) {}
Lexer::~Lexer() {}

const string& Lexer::getValue() {
  for (char c : chars) {
    value += c;
  }
  chars.empty();
}
