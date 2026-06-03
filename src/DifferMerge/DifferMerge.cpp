#include <unordered_map>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <cctype>

using std::vector;
using std::unordered_map;
using std::string;
using std::list;
using std::erase_if;
using std::isspace;

class DifferMerge {
  private:
    unordered_map<string, list<string>> differ;
  public:
    unordered_map<string, list<string>>& getDiffer();
    void merge(vector<unordered_map<string, list<string>>>& differs);
    DifferMerge();
};

DifferMerge::DifferMerge() {}

unordered_map<string, list<string>>& DifferMerge::getDiffer() {
  return differ;
}

void DifferMerge::merge(vector<unordered_map<string, list<string>>>& differs) {
  for (const auto& d : differs) {
    for (const auto& [key, list1] : d) {
      for (const auto& lineText : list1) {
        string location = key;
        erase_if(location, [](unsigned char ch) {
          return isspace(ch);
        });
        if (differ.find(location) != differ.end()) {
          differ[location].push_back(lineText);
        } else {
          list<string> newList = {lineText};
          differ[location] = newList;
        }
      }
    }
  }
}
