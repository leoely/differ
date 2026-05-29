#include <iostream>
#include <string>
#include <list>
#include <termcolor/termcolor.hpp>

using std::cout;
using std::endl;
using std::string;
using std::list;

class Parser {
  protected:
    string key;
    int line, position;
    list<char> chars;
    void obtainKey();
    void showError(const string &lineText, const string &message);
    int getWidth(int position);
  public:
    Parser();
    ~Parser();
};

Parser::Parser() : key(""), line(0), position(0) {}
Parser::~Parser() {}
void Parser::obtainKey() {
  for (auto e: this->chars) {
    this->key += e;
  }
  this->chars.clear();
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
