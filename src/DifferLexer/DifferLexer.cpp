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
  public:
    DifferLexer();
    ~DifferLexer();
    void scanLine(const string& lineText, bool add);
    void addToken(DifferTokenType type, const string& elem);
    vector<shared_ptr<DifferToken>>& getTokens();
  private:
    void dealChar(char c, bool add);
    bool flag;
    vector<shared_ptr<DifferToken>> tokens;
    int status;
};

DifferLexer::DifferLexer() : Lexer(), status(0), flag(false) {}
DifferLexer::~DifferLexer() {}

vector<shared_ptr<DifferToken>>& DifferLexer::getTokens() {
  return tokens;
}

void DifferLexer::addToken(DifferTokenType type, const string& elem) {
  shared_ptr<DifferToken> token(new DifferToken{ type, elem, });
  tokens.push_back(token);
}

void DifferLexer::scanLine(const string& lineText, bool add) {
  position = 0;
  for (char c: lineText) {
    if (flag == false) {
      if (c != ' ') {
        dealChar(c, add);
      } else {
        if (add == true) {
          addToken(DifferTokenType::BLANK, " ");
        }
      }
    } else {
      dealChar(c, add);
    }
    position += 1;
  }
  line += 1;
  if (flag == false) {
    if (add == true) {
      addToken(DifferTokenType::LINE_BREAK, "\n");
    }
  } else {
    dealChar('\n', add);
  }
}

void DifferLexer::dealChar(char c, bool add) {
  switch (status) {
    case 0:
      switch (c) {
        case '=':
          if (add == true) {
            addToken(DifferTokenType::EQUAL, "=");
          }
          status = 1;
          break;
        case '"':
          if (add == true) {
            addToken(DifferTokenType::COLON, "\"");
          }
          status = 5;
          break;
        case '|':
          if (add == true) {
            addToken(DifferTokenType::DIVIDER, "|");
          }
          status = 4;
          break;
        default:
          status = 6;
      }
      break;
    case 1:
      if (c == '{') {
        if (add == true) {
          addToken(DifferTokenType::CURLY_BRACE, "{");
        }
        status = 2;
      }
      break;
    case 2:
      if (c == '%') {
        if (add == true) {
          addToken(DifferTokenType::PERCENTAGE, "%");
        }
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
        if (add == true) {
          addToken(DifferTokenType::LOCATION, location);
          addToken(DifferTokenType::CURLY_BRACE, "}");
        }
        status = 0;
      } else {
        if (add == true) {
          chars.push_back(c);
        }
      }
    case 4:
      flag = true;
      switch (c) {
        case ' ':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
            addToken(DifferTokenType::BLANK, " ");
          }
          value.clear();
          break;
        case '\n':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
            addToken(DifferTokenType::LINE_BREAK, "\n");
          }
          value.clear();
          break;
        case '|':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(DifferTokenType::DIVIDER, "|");
          }
          flag = false;
          break;
        case '"':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(DifferTokenType::COLON, "\"");
          }
          flag = false;
          break;
        case '=':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(DifferTokenType::EQUAL, "=");
          }
          flag = false;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
    case 5:
      flag = true;
      switch (c) {
        case ' ':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
            addToken(DifferTokenType::BLANK, " ");
          }
          value.clear();
          break;
        case '\n':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
            addToken(DifferTokenType::LINE_BREAK, "\n");
          }
          value.clear();
          break;
        case '"':
          if (add == true) {
            addToken(DifferTokenType::COMMENT, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(DifferTokenType::COLON, "\"");
          }
          status = 0;
          flag = false;
          break;
        case '=':
          if (add == true) {
            addToken(DifferTokenType::COMMENT, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(DifferTokenType::EQUAL, "=");
          }
          status = 0;
          flag = false;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
    case 6:
      flag = true;
      switch (c) {
        case ' ':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
            addToken(DifferTokenType::BLANK, " ");
          }
          value.clear();
          break;
        case '\n':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
            addToken(DifferTokenType::LINE_BREAK, "\n");
          }
          value.clear();
          break;
        case '"':
          if (add == true) {
            addToken(DifferTokenType::MULTIPLE, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(DifferTokenType::COLON, "\"");
          }
          status = 0;
          flag = false;
          break;
        case '=':
          if (add == true) {
            addToken(DifferTokenType::MULTIPLE, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(DifferTokenType::EQUAL, "=");
          }
          status = 1;
          flag = false;
          break;
        case '|':
          if (add == true) {
            addToken(DifferTokenType::DIVIDER, "|");
          }
          status = 4;
          flag = false;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
  }
}
