#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

class VariableMerge {
  private:
    unordered_map<string, string> variable;
  public:
    VariableMerge();
    void merge(vector<unordered_map<string, string>>& variables);
    unordered_map<string, string>& getVariable();
};

VariableMerge::VariableMerge() {}

unordered_map<string, string>& VariableMerge::getVariable() {
  return variable;
}

void VariableMerge::merge(vector<unordered_map<string, string>>& variables) {
  variable.clear();
  for (const auto& v : variables) {
    for (const auto& [key, value] : v) {
      variable[key]= value;
    }
  }
}
