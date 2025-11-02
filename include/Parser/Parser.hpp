#pragma once

#include <iostream>
#include <string>
#include <list>

using namespace std;

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
