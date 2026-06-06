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
    dealChar(c, add);
    position += 1;
  }
  line += 1;
  dealChar('\n', add);
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
        case '\n':
          if (add == true) {
            addToken(DifferTokenType::LINE_BREAK, "\n");
          }
          break;
        default:
          chars.push_back(c);
          status = 6;
      }
      break;
    case 1:
      switch (c) {
        case '{':
          if (add == true) {
            addToken(DifferTokenType::CURLY_BRACE, "{");
          }
          status = 2;
          break;
      }
      break;
    case 2:
      switch (c) {
        case '%':
          if (add == true) {
            addToken(DifferTokenType::PERCENTAGE, "%");
          }
          status = 3;
          break;
      }
      break;
    case 3:
      switch (c) {
        case '}':
          if (add == true) {
            addToken(DifferTokenType::LOCATION, getValue());
            addToken(DifferTokenType::CURLY_BRACE, "}");
          }
          status = 4;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
    case 4:
      switch (c) {
        case '\n':
          if (add == true) {
            addToken(DifferTokenType::LINE_BREAK, "\n");
          }
          break;
        case '|':
          if (add == true) {
            addToken(DifferTokenType::BAR, "|");
          }
          status = 9;
          break;
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
        default:
          status = 0;
          chars.push_back(c);
      }
      break;
    case 5:
      flag = true;
      switch (c) {
        case ' ':
          if (add == true) {
            addToken(DifferTokenType::COMMENT, getValue());
            addToken(DifferTokenType::BLANK, " ");
          }
          break;
        case '\n':
          if (add == true) {
            addToken(DifferTokenType::COMMENT, getValue());
            addToken(DifferTokenType::LINE_BREAK, "\n");
          }
          status = 0;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
    case 6:
      switch (c) {
        case ' ':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
            addToken(DifferTokenType::BLANK, " ");
          }
          break;
        case '\n':
          if (add == true) {
            addToken(DifferTokenType::SINGLE, getValue());
            addToken(DifferTokenType::LINE_BREAK, "\n");
          }
          status = 0;
          break;
        case '#':
          status = 7;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
    case 7:
      switch (c) {
        case '{':
          status = 8;
          break;
        default:
          chars.push_back('#');
          chars.push_back(c);
          status = 6;
      }
      break;
    case 8:
      switch (c) {
        case '}':
          if (add == true) {
            addToken(DifferTokenType::HASHTAG, "#");
            addToken(DifferTokenType::CURLY_BRACE, "{");
            addToken(DifferTokenType::VARIABLE, getValue());
            addToken(DifferTokenType::CURLY_BRACE, "}");
          }
          status = 6;
          break;
        default:
          chars.push_back(c);
      }
      break;
    case 9:
      switch (c) {
        case ' ':
          if (add == true) {
            addToken(DifferTokenType::MULTIPLE, getValue());
            addToken(DifferTokenType::BLANK, " ");
          }
          break;
        case '\n':
          if (add == true) {
            addToken(DifferTokenType::MULTIPLE, getValue());
            addToken(DifferTokenType::LINE_BREAK, "\n");
          }
          status = 4;
          break;
        case '#':
          status = 7;
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
  }
}
