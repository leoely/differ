#pragma once

#include <string>
#include <LocationTokenType/LocationTokenType.hpp>
#include <Lexer/Lexer.hpp>

using std::string;

class LocationLexer : public virtual Lexer {
  using Lexer::Lexer;
  public:
    LocationLexer::LocationLexer();
    LocationLexer::~LocationLexer();
    void scanLine(string line);
  private:
    string value;
    int status;
    void dealChar(char c);
    const string& getValue();
}
