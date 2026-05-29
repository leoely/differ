#pragma once

#include <string>
#include <Lexer/Lexer>
#include <DifferTokenType/DifferTokenType>

using std::string;

class DifferLexer : public virtual Lexer {
  using Lexer::Lexer;
  public:
    DifferLexer::DifferLexer();
    DifferLexer::~DifferLexer();
    void scanLine(string& line);
  private:
    string value;
    int status;
    void dealChar(char c);
}
