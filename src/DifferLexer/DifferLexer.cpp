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
    bool flag;
    vector<shared_ptr<DifferToken>> tokens;
    int status;
    void dealChar(char c);
};

DifferLexer::DifferLexer() : status(0), flag(false) {}
DifferLexer::~DifferLexer() {}

vector<shared_ptr<DifferToken>>& DifferLexer::getTokens() {
  return tokens;
}

void DifferLexer::addToken(DifferTokenType type, const string& elem) {
  shared_ptr<DifferToken> token(new DifferToken{ type, elem, });
  tokens.push_back(token);
}

void DifferLexer::scanLine(const string& lineText) {
  position = 0;
  for (char c: lineText) {
    if (flag == false) {
      if (c != ' ') {
        dealChar(c);
      } else {
        addToken(DifferTokenType::BLANK, " ");
      }
    } else {
      dealChar(c);
    }
    position += 1;
  }
  line += 1;
  if (flag == false) {
    addToken(DifferTokenType::LINE_BREAK, "\n");
  } else {
    dealChar('\n');
  }
}

void DifferLexer::dealChar(char c) {
  switch (status) {
    case 0:
      switch (c) {
        case '=':
          addToken(DifferTokenType::EQUAL, "=");
          status = 1;
          break;
        case '"':
          addToken(DifferTokenType::COLON, "\"");
          status = 5;
          break;
        case '|':
          addToken(DifferTokenType::DIVIDER, "|");
          status = 4;
          break;
        default:
          status = 6;
      }
      break;
    case 1:
      if (c == '{') {
        addToken(DifferTokenType::CURLY_BRACE, "{");
        status = 2;
      }
      break;
    case 2:
      if (c == '%') {
        addToken(DifferTokenType::PERCENTAGE, "%");
        status = 3;
      }
      break;
    case 3:
      if (c == '}') {
        string location;
        for (char c : this->chars) {
          location += c;
        }
        chars.clear();
        addToken(DifferTokenType::LOCATION, location);
        addToken(DifferTokenType::CURLY_BRACE, "}");
        status = 0;
      } else {
        chars.push_back(c);
      }
    case 4:
      flag = true;
      switch (c) {
        case ' ':
          addToken(DifferTokenType::SINGLE, getValue());
          addToken(DifferTokenType::BLANK, " ");
          value.clear();
          break;
        case '\n':
          addToken(DifferTokenType::SINGLE, getValue());
          addToken(DifferTokenType::LINE_BREAK, "\n");
          value.clear();
          break;
        case '|':
          addToken(DifferTokenType::SINGLE, getValue());
          value.clear();
          addToken(DifferTokenType::DIVIDER, "|");
          flag = false;
          break;
        case '"':
          addToken(DifferTokenType::SINGLE, getValue());
          value.clear();
          addToken(DifferTokenType::COLON, "\"");
          flag = false;
          break;
        case '=':
          addToken(DifferTokenType::SINGLE, getValue());
          value.clear();
          addToken(DifferTokenType::EQUAL, "=");
          flag = false;
          break;
        default:
          chars.push_back(c);
      }
      break;
    case 5:
      flag = true;
      switch (c) {
        case ' ':
          addToken(DifferTokenType::SINGLE, getValue());
          addToken(DifferTokenType::BLANK, " ");
          value.clear();
          break;
        case '\n':
          addToken(DifferTokenType::SINGLE, getValue());
          addToken(DifferTokenType::LINE_BREAK, "\n");
          value.clear();
          break;
        case '"':
          addToken(DifferTokenType::COMMENT, getValue());
          value.clear();
          addToken(DifferTokenType::COLON, "\"");
          status = 0;
          flag = false;
          break;
        case '=':
          addToken(DifferTokenType::COMMENT, getValue());
          value.clear();
          addToken(DifferTokenType::EQUAL, "=");
          status = 0;
          flag = false;
          break;
        default:
          chars.push_back(c);
      }
      break;
    case 6:
      flag = true;
      switch (c) {
        case ' ':
          addToken(DifferTokenType::SINGLE, getValue());
          addToken(DifferTokenType::BLANK, " ");
          value.clear();
          break;
        case '\n':
          addToken(DifferTokenType::SINGLE, getValue());
          addToken(DifferTokenType::LINE_BREAK, "\n");
          value.clear();
          break;
        case '"':
          addToken(DifferTokenType::MULTIPLE, getValue());
          value.clear();
          addToken(DifferTokenType::COLON, "\"");
          status = 0;
          flag = false;
          break;
        case '=':
          addToken(DifferTokenType::MULTIPLE, getValue());
          value.clear();
          addToken(DifferTokenType::EQUAL, "=");
          status = 1;
          flag = false;
          break;
        case '|':
          addToken(DifferTokenType::DIVIDER, "|");
          status = 4;
          flag = false;
          break;
        default:
          chars.push_back(c);
      }
      break;
  }
}
