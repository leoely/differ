#pragma once

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
    int getWidth(int position);
  public:
    Parser();
    ~Parser();
};
