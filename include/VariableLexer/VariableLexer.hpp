#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <VariableTokenType/VariableTokenType.hpp>
#include <VariableToken/VariableToken.hpp>
#include <Lexer/Lexer.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

class VariableLexer : public virtual Lexer {
  public:
    string key;
    VariableLexer();
    void scanLine(const string& lineText, bool add);
    vector<shared_ptr<VariableToken>>& getTokens();
  private:
    void addToken(VariableTokenType type, string elem);
    vector<shared_ptr<VariableToken>> tokens;
    int status;
    void dealChar(char c, bool add);
};
