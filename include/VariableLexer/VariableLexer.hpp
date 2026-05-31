#pragma once

#include <memory>
#include <vector>
#include <string>
#include <VariableTokenType/VariableTokenType.hpp>
#include <VariableToken/VaraibleToken.hpp>
#include <Lexer/Lexer.hpp>

class VariableLexer : public virtual Lexer {
  public:
    string key;
    VariableLexer();
    void scanLine(const string& lineText);
    vector<shared_ptr<LocationToken>>& getTokens();
  private:
    void addToken(LocationTokenType type, string elem);
    vector<shared_ptr<LocationToken>> tokens;
    int status;
    void dealChar(char c);
}
