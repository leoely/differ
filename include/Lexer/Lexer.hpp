#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <Token/Token.hpp>

using std::string;
using std::vector;

class Lexer {
  protect:
    int line, position;
    list<char> chars;
    vector<Token> tokens;
    void addToken(string type, string elem);
  public:
    Lexer::Lexer();
    Lexer::~Lexer();
    const vector<Token>& Lexer::getTokens();
    void showError(int errorCode);
    const string& getValue();
}
