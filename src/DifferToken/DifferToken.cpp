#include <string>
#include <DifferTokenType/DifferTokenType.hpp>

using std::string;

class DifferToken {
  public:
    DifferTokenType type;
    string elem;
    Token(DifferTokenType t, const string& e);
    ~Token();
};

Token::Token(DifferTokenType t, const string& e) : type(t), elem(e) {}
Token::~Token() {}
