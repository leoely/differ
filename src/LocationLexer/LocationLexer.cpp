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
    LocationLexer();
    void scanLine(const string& lineText);
    vector<shared_ptr<LocationToken>>& getTokens();
  private:
    void addToken(LocationTokenType type, string elem);
    vector<shared_ptr<LocationToken>> tokens;
    int status;
    void dealChar(char c);
};

LocationLexer::LocationLexer() : Lexer(), status(0) {}

vector<shared_ptr<LocationToken>>& LocationLexer::getTokens() {
  return tokens;
}

void LocationLexer::addToken(LocationTokenType type, string elem) {
  shared_ptr<LocationToken> token(new LocationToken{type, elem});
  tokens.push_back(token);
}

void LocationLexer::scanLine(const string& lineText) {
  position = 0;
  for (char c: lineText) {
    if (c != ' ') {
      dealChar(c);
    } else {
      addToken(LocationTokenType::BLANK, " ");
    }
    position += 1;
  }
  line += 1;
  addToken(LocationTokenType::LINE_BREAK, "\n");
}


void LocationLexer::dealChar(char c) {
  switch (status) {
    case 0:
      if (c == '%') {
        addToken(LocationTokenType::PERCENTAGE, "%");
        status = 2;
      }
      break;
    case 1:
      if (c == '*') {
        string key;
        for (char c : this->chars) {
          key += c;
        }
        addToken(LocationTokenType::KEY, key);
        addToken(LocationTokenType::ASTERISK, "*");
        chars.clear();
        status = 2;
      } else {
        chars.push_back(c);
      }
      break;
    case 2:
      if (c == '=') {
        addToken(LocationTokenType::EQUAL, "=");
        status = 3;
      }
      break;
    case 3:
      if (c == '[') {
        addToken(LocationTokenType::SQUARE_BRACKET, "[");
        status = 4;
      }
      break;
    case 4:
      switch (c) {
        case ']':
          addToken(LocationTokenType::VALUE, getValue());
          value.clear();
          addToken(LocationTokenType::SQUARE_BRACKET, "]");
          status = 0;
          break;
        case '&':
          addToken(LocationTokenType::VALUE, getValue());
          value.clear();
          addToken(LocationTokenType::AND, "&");
          break;
        default:
          chars.push_back(c);
      }
      break;
  }
}
