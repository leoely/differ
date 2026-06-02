#pragma once

#include <memory>
#include <vector>
#include <string>
#include <LocationTokenType/LocationTokenType.hpp>
#include <LocationToken/LocationToken.hpp>
#include <Lexer/Lexer.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

class LocationLexer : virtual public Lexer {
  public:
    string key;
    LocationLexer();
    ~LocationLexer();
    void scanLine(const string& lineText, bool add);
    vector<shared_ptr<LocationToken>>& getTokens();
    void dealChar(char c, bool add);
  private:
    void addToken(LocationTokenType type, string elem);
    vector<shared_ptr<LocationToken>> tokens;
    int status;
};
