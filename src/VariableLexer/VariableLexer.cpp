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
    void scanLine(const string& lineText);
    vector<shared_ptr<VariableToken>>& getTokens();
  private:
    void addToken(VariableTokenType type, string elem);
    vector<shared_ptr<VariableToken>> tokens;
    int status;
    void dealChar(char c);
};

VariableLexer::VariableLexer() : Lexer(), status(0) {}

vector<shared_ptr<VariableToken>>& VariableLexer::getTokens() {
  return tokens;
}

void VariableLexer::addToken(VariableTokenType type, string elem) {
  shared_ptr<VariableToken> token(new VariableToken{type, elem});
  tokens.push_back(token);
}

void VariableLexer::scanLine(const string& lineText) {
  position = 0;
  for (char c: lineText) {
    if (c != ' ') {
      dealChar(c);
    } else {
      addToken(VariableTokenType::BLANK, " ");
    }
    position += 1;
  }
  line += 1;
  dealChar('\n');
}


void VariableLexer::dealChar(char c) {
  switch (status) {
    case 0:
      if (c == '^') {
        addToken(VariableTokenType::CARET, "^");
        status = 1;
      }
      break;
    case 1:
      if (c == '(') {
        addToken(VariableTokenType::BRACKET, "(");
        status = 2;
      }
      break;
    case 2:
      if (c == ')') {
        addToken(VariableTokenType::KEY, getValue());
        key.clear();
        addToken(VariableTokenType::BRACKET, ")");
        status = 3;
      } else {
        chars.push_back(c);
      }
      break;
    case 3:
      if (c == '=') {
        addToken(VariableTokenType::EQUAL, "=");
        status = 4;
      }
      break;
    case 4:
      if (c == '"') {
        addToken(VariableTokenType::COLON, "\"");
        status = 5;
      }
      break;
    case 5:
      if (c == '"') {
        addToken(VariableTokenType::VALUE, getValue());
        addToken(VariableTokenType::COLON, "\"");
        status = 0;
      } else {
        chars.push_back(c);
      }
      break;
  }
}
