#pragma once

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
