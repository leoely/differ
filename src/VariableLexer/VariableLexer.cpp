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

VariableLexer::VariableLexer() : Lexer(), status(0)  {}

vector<shared_ptr<VariableToken>>& VariableLexer::getTokens() {
  return tokens;
}

void VariableLexer::addToken(VariableTokenType type, string elem) {
  shared_ptr<VariableToken> token(new VariableToken{type, elem});
  tokens.push_back(token);
}

void VariableLexer::scanLine(const string& lineText, bool add) {
  position = 0;
  for (char c: lineText) {
    if (c != ' ') {
      dealChar(c, add);
    } else {
      if (add == true) {
        addToken(VariableTokenType::BLANK, " ");
      }
    }
    position += 1;
  }
  line += 1;
  dealChar('\n', add);
}


void VariableLexer::dealChar(char c, bool add) {
  switch (status) {
    case 0:
      switch (c) {
        case '^':
          if (add == true) {
            addToken(VariableTokenType::CARET, "^");
          }
          status = 1;
          break;
      }
      break;
    case 1:
      switch (c) {
        case '(':
          if (add == true) {
            addToken(VariableTokenType::BRACKET, "(");
          }
          status = 2;
          break;
      }
      break;
    case 2:
      switch (c) {
        case '\n':
          if (add == true) {
            addToken(VariableTokenType::KEY, getValue());
            addToken(VariableTokenType::LINE_BREAK, "\n");
          }
          break;
        case ' ':
          if (add == true) {
            addToken(VariableTokenType::KEY, getValue());
            addToken(VariableTokenType::BLANK, " ");
          }
          break;
        case ')':
          if (add == true) {
            addToken(VariableTokenType::KEY, getValue());
          }
          key.clear();
          if (add == true) {
            addToken(VariableTokenType::BRACKET, ")");
          }
          status = 3;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
    case 3:
      switch (c) {
        case '=':
          if (add == true) {
            addToken(VariableTokenType::EQUAL, "=");
          }
          status = 4;
          break;
      }
      break;
    case 4:
      switch (c) {
        case '"':
          if (add == true) {
            addToken(VariableTokenType::COLON, "\"");
          }
          status = 5;
          break;
      }
      break;
    case 5:
      switch (c) {
        case '\n':
          if (add == true) {
            addToken(VariableTokenType::VALUE, getValue());
            addToken(VariableTokenType::LINE_BREAK, "\n");
          }
          break;
        case ' ':
          if (add == true) {
            addToken(VariableTokenType::VALUE, getValue());
            addToken(VariableTokenType::BLANK, "\"");
          }
          break;
        case '"':
          if (add == true) {
            addToken(VariableTokenType::VALUE, getValue());
            addToken(VariableTokenType::COLON, "\"");
          }
          status = 0;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
  }
}
