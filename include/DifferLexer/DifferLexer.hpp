#pragma once

#include <vector>
#include <memory>
#include <string>
#include <Lexer/Lexer.hpp>
#include <DifferToken/DifferToken.hpp>
#include <DifferTokenType/DifferTokenType.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

class DifferLexer : public virtual Lexer {
  using Lexer::Lexer;
  public:
    DifferLexer();
    ~DifferLexer();
    void scanLine(const string& lineText);
    void addToken(DifferTokenType type, const string& elem);
    vector<shared_ptr<DifferToken>>& getTokens();
  private:
    vector<shared_ptr<DifferToken>> tokens;
    int status;
    void dealChar(char c);
};
