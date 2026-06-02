#include <string>
#include <list>
#include <termcolor/termcolor.hpp>

using std::string;
using std::list;

class Parser {
  protected:
    string word;
    int line, position;
    list<char> chars;
    string fullPath;
    string& obtainWord();
    int getWidth(int position);
  public:
    Parser();
    ~Parser();
};

Parser::Parser() : word(""), line(0), position(0) {}
Parser::~Parser() {}

string& Parser::obtainWord() {
  word = "";
  for (auto e: chars) {
    word += e;
  }
  chars.clear();
  return word;
}

int Parser::getWidth(int position) {
  int width = 1;
  while (position >= 10) {
    float quotient = position / 10;
    position = static_cast<int>(quotient);
    width += 1;
  }
  return width;
}
