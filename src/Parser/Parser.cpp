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

inline int getWidth(int position) {
  int width = 1;
  while (position >= 10) {
    float quotient = position / 10;
    position = static_cast<int>(quotient);
    width += 1;
  }
  return width;
}

void Parser::showError(const string &lineText, const string &message) {
  cout << "" << endl;
  cout << termcolor::dark << line << " " << termcolor::reset << termcolor::on_white << termcolor::color<0, 0, 0> << lineText << termcolor::reset << endl;
  int blankCount = getWidth(line) + position + 1;
  for (int i = 0; i < blankCount - 2; i += 1) {
    cout << " ";
  }
  cout << termcolor::dark << "[[" << termcolor::reset<< termcolor::bold << "|" << termcolor::reset << termcolor::dark << "]]" << termcolor::reset << endl;
  cout << "" << endl;
  cout << termcolor::bold << "Line: " << termcolor::reset << line << "," << termcolor::bold << " Pos: " << termcolor::reset << position << ";" << endl;
  cout << message << endl;
}
