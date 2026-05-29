#include <string>
#include <LocationTokenType/LocationTokenType.hpp>

using std::string;

class LocationToken {
  public:
    LocationTokenType type;
    string elem;
    Token(LocationTokenType t, const string& e);
    ~Token();
};

Token::Token(LocationTokenType t, const string& e) : type(t), elem(e) {}
Token::~Token() {}
