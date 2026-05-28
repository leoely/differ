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
    int status;
    void dealChar(char c);
}

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <Token/Token.hpp>

using std::string;
using std::vector;

class Lexer {
  protect:
    int line, position;
    list<char> chars;
    vector<Token> tokens;
    void addToken(string type, string elem);
  public:
    Lexer::Lexer();
    Lexer::~Lexer();
    const vector<Token>& Lexer::getTokens();
    void showError(int errorCode);
    const string& getValue();
}
