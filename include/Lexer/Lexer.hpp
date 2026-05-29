#pragma once

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
