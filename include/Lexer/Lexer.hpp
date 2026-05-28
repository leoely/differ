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

