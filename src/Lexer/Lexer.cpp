#include <memory>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <Token/Token.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

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

Lexer::Lexer() : line(0), position(0) {}
Lexer::~Lexer() {}

const string& LocationLexer::getValue() {
  for (char c : this->chars) {
    value += c;
  }
  chars.empty();
}

void Lexer::addToken(string type, string elem) {
  shared_ptr<Token> token(Token(type, elem));
  tokens.push_back(token);
}

const vector<Token>& Lexer::getTokens() {
  return tokens;
}
