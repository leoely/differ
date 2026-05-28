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
    int status;
    void dealChar(char c);
}
