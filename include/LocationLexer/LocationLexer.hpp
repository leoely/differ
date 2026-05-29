#pragma once

#include <string>
#include <LocationTokenType/LocationTokenType.hpp>
#include <LocationToken/LocationToken.hpp>
#include <Lexer/Lexer.hpp>

using std::string;

class LocationLexer : public virtual Lexer {
  using Lexer::Lexer;
  public:
    LocationLexer();
    ~LocationLexer();
    void scanLine(const string& lineText);
    vector<shared_ptr<LocationToken>>& getTokens();
  private:
    void addToken(const LocationTokenType& type, const string& elem);
    vector<shared_ptr<LocationToken>> tokens;
    string value;
    int status;
    void dealChar(char c);
    const string& getValue();
};
