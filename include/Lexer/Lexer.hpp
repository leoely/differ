#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>

using std::list;
using std::string;
using std::vector;
using std::shared_ptr;

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
