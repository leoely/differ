#pragma once

#include <string>
#include <Lexer/Lexer.hpp>
#include <DifferTokenType/DifferTokenType.hpp>

using std::string;

class DifferLexer : public virtual Lexer {
  using Lexer::Lexer;
  public:
    DifferLexer();
    ~DifferLexer();
    void scanLine(const string& line);
    void addToken(DifferTokenType type, const string& elem);
    vector<shared_ptr<DifferToken>>& getTokens();
  private:
    vector<shared_ptr<DifferToken>> tokens;
    string value;
    int status;
    void dealChar(char c);
};
