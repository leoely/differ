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
        addToken(VariableToken::CARET, "^");
        status = 1;
      }
      break;
    case 1:
      if (c == '(') {
        addToken(VariableToken::BRACKET, "(");
        status = 2;
      }
      break;
    case 2:
      if (c == ')') {
        addToken(VaraibleToken::KEY, getValue());
        key.clear();
        addToken(VariableToken::BRACKET, "(");
        status = 3;
      } else {
        chars.push_back(c);
      }
      break;
    case 3:
      if (c == '=') {
        addToken(VariableToken::EQUAL, "=");
        status = 4;
      }
      break;
    case 4:
      if (c == '"') {
        addToken(VariableToken::COLON, "\"");
        status = 5;
      }
      break;
    case 5:
      if (c == '"') {
        addToken(VariableToken::VALUE, getValue());
        addToken(VariableToken::COLON, "\"");
        status = 0;
      } else {
        chars.push(c);
      }
      break;
  }
}
