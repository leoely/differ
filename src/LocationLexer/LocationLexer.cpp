#include <memory>
#include <vector>
#include <string>
#include <LocationTokenType/LocationTokenType.hpp>
#include <LocationToken/LocationToken.hpp>
#include <Lexer/Lexer.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

class LocationLexer : virtual public Lexer {
  public:
    string key;
    LocationLexer();
    ~LocationLexer();
    void scanLine(const string& lineText, bool add);
    vector<shared_ptr<LocationToken>>& getTokens();
  private:
    void dealChar(char c, bool add);
    void addToken(LocationTokenType type, string elem);
    vector<shared_ptr<LocationToken>> tokens;
    int status;
};

LocationLexer::LocationLexer() : Lexer(), status(0) {}
LocationLexer::~LocationLexer() {}

vector<shared_ptr<LocationToken>>& LocationLexer::getTokens() {
  return tokens;
}

void LocationLexer::addToken(LocationTokenType type, string elem) {
  shared_ptr<LocationToken> token(new LocationToken{type, elem});
  tokens.push_back(token);
}

void LocationLexer::scanLine(const string& lineText, bool add) {
  position = 0;
  for (char c: lineText) {
    if (c != ' ') {
      dealChar(c, add);
    } else {
      if (add == true) {
        addToken(LocationTokenType::BLANK, " ");
      }
    }
    position += 1;
  }
  line += 1;
  dealChar('\n', add);
}


void LocationLexer::dealChar(char c, bool add) {
  switch (status) {
    case 0:
      if (c == '%') {
        if (add == true) {
          addToken(LocationTokenType::PERCENTAGE, "%");
        }
        status = 2;
      } else if (c == '\n') {
        if (add == true) {
          addToken(LocationTokenType::LINE_BREAK, "\n");
        }
      }
      break;
    case 1:
      switch (c) {
        case ' ':
          if (add == true) {
            addToken(LocationTokenType::KEY, getValue());
            addToken(LocationTokenType::BLANK, " ");
          }
        case '*':
          if (add == true) {
            addToken(LocationTokenType::KEY, getValue());
            addToken(LocationTokenType::ASTERISK, "*");
          }
          status = 2;
          break;
        case '\n':
          if (add == true) {
            addToken(LocationTokenType::KEY, getValue());
            addToken(LocationTokenType::LINE_BREAK, "\n");
          }
          break;
        default:
        if (add == true) {
          chars.push_back(c);
        }
      }
      break;
    case 2:
      if (c == '=') {
        if (add == true) {
          addToken(LocationTokenType::EQUAL, "=");
        }
        status = 3;
      }
      break;
    case 3:
      if (c == '[') {
        if (add == true) {
          addToken(LocationTokenType::SQUARE_BRACKET, "[");
        }
        status = 4;
      }
      break;
    case 4:
      switch (c) {
        case ' ':
          if (add == true) {
            addToken(LocationTokenType::VALUE, getValue());
            addToken(LocationTokenType::BLANK, " ");
          }
          break;
        case ']':
          if (add == true) {
            addToken(LocationTokenType::VALUE, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(LocationTokenType::SQUARE_BRACKET, "]");
          }
          status = 0;
          break;
        case '&':
          if (add == true) {
            addToken(LocationTokenType::VALUE, getValue());
          }
          value.clear();
          if (add == true) {
            addToken(LocationTokenType::AND, "&");
          }
          break;
        case '\n':
          if (add == true) {
            addToken(LocationTokenType::VALUE, getValue());
            addToken(LocationTokenType::LINE_BREAK, "\n");
          }
          value.clear();
          break;
        default:
          if (add == true) {
            chars.push_back(c);
          }
      }
      break;
  }
}
