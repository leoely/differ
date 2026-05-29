#include <string>
#include <LocationTokenType/LocationTokenType.hpp>

using std::string;

class LocationToken {
  public:
    LocationTokenType type;
    string elem;
    LocationToken(LocationTokenType t, const string& e);
    ~LocationToken();
};

LocationToken::LocationToken(LocationTokenType t, const string& e) : type(t), elem(e) {}
LocationToken::~LocationToken() {}
