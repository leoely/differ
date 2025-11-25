#pragma once

#include <iostream>
#include <string>
#include <list>

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
