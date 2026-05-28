#include <string>

using std::string;

class Token {
  public:
    string type, elem;
    Token(string t, string e);
    ~Token();
}

Token::Token(string t, string e) : type(t) : elem(e) {}
Token::~Token() {}
