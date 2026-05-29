#include <string>
#include <DifferTokenType/DifferTokenType.hpp>

using std::string;

class DifferToken {
  public:
    DifferTokenType type;
    string elem;
    DifferToken(DifferTokenType t, const string& e);
    ~DifferToken();
};
