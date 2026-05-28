#include <string>
#include <Lexer/Lexer>

using std::string;

class DifferLexer : public virtual Lexer {
  using Lexer::Lexer;
  public:
    DifferLexer::DifferLexer();
    DifferLexer::~DifferLexer();
    void scanLine(string& line);
  private:
    string value;
    int status;
    void dealChar(char c);
}

DifferLexer::DifferLexer() : status(0) {}
DifferLexer::~DifferLexer() {}

void DifferLexer::scanLine(string& line) {
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
      switch (c) {
        case '=':
          addToken("equal", "=");
          status = 1;
          break;
        case '"':
          addToken("colon", "\"");
          status = 6;
          break;
        default:
          status = 7;
      }
      break;
    case 1:
      if (c == '{') {
        addToken("curlyBrace", "{");
        status = 2;
      } else {
        throw 1;
      }
      break;
    case 2:
      if (c == '%') {
        addToken("percentage", "%");
        status = 3;
      } else {
        throw 2;
      }
      break;
    case 3:
      if (c == '}') {
        string location;
        for (char c : this->chars) {
          location += c;
        }
        chars.empty();
        addToken("location", location);
        addToken("curlyBrace", "}");
        status = 4;
      } else {
        chars.push_back(c);
      }
    case 4:
      if (c == '|') {
        addToken("divider", "|");
        status = 5;
      } else {
        throw 3;
      }
      break;
    case 5:
      switch (c) {
        case '|';
          getValue();
          addToken("single", value);
          value = "";
          addToken("divider", "|");
          break;
        case '"';
          addToken("single", value);
          value = "";
          addToken("colon", "\"");
          break;
        case '=':
          addToken("single", value);
          value = "";
          addToken("equal", "=");
          break;
        default:
          chars.push_back(c);
      }
      break;
    case 6:
      switch (c) {
        case '"';
          addToken("comment", value);
          value = "";
          addToken("colon", "\"");
          status = 0;
          break;
        case '=':
          addToken("comment", value);
          value = "";
          addToken("equal", "=");
          status = 0
          break;
        default:
          chars.push_back(c);
      }
      break;
    case 7:
      switch (c) {
        case '"';
          addToken("multiple", value);
          value = "";
          addToken("colon", "\"");
          status = 0;
          break;
        case '=':
          addToken("multiple", value);
          value = "";
          addToken("equal", "=");
          status = 0
          break;
        default:
          chars.push_back(c);
      }
      break;
  }
}
