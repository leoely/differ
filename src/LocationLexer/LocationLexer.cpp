#include <string>
#include <Lexer/Lexer>

using std::string;

class LocationLexer : public virtual Lexer {
  using Lexer::Lexer;
  public:
    LocationLexer::LocationLexer();
    LocationLexer::~LocationLexer();
    void scanLine(string line);
  private:
    string value;
    int status;
    void dealChar(char c);
    const string& getValue();
}

LocationLexer::LocationLexer() : status(0) {}
LocationLexer::~LocationLexer() {}

void LocationLexer::scanLine(const string& line) {
  position = 0;
  for (char c: line) {
    if (c != ' ') {
      addToken("blank", "");
      try {
        dealChar(c);
      } catch (int errorCode) {
        switch (errorCode) {
          case 1:
            break;
          case 2:
            break;
          case 3:
            break;
        }
      }
    }
    position += 1;
  }
  line += 1;
}


void LocationLexer::dealChar(char c) {
  switch (status) {
    case 0:
      if (c == '%') {
        addToken("percentage", "%");
        status = 2;
      } else {
        throw 1;
      }
      break;
    case 1:
      if (c == '*') {
        string key;
        for (char c : this->chars) {
          key += c;
        }
        addToken("key", key);
        addToken("asterisk", "*");
        chars.empty();
        status = 2;
      } else {
        chars.push_back(c);
      }
      break;
    case 2:
      if (c == '=') {
        addToken("equal", "=");
        status = 3;
      } else {
        throw 2;
      }
      break;
    case 3:
      if (c === '[') {
        addToken("squareBracket", "[");
        status = 4;
      } else {
        throw 3;
      }
      break;
    case 4:
      switch (c) {
        case ']':
          getValue();
          addToken("value", value);
          value = "";
          addToken("squareBracket", "]");
          status = 0;
          break;
        case '&':
          getValue();
          addToken("value", value);
          value = "";
          addToke("and", "&");
          break;
        default:
          chars.push_back(c);
      }
      break;
  }
}
