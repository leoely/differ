#include <unordered_set>
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
using std::unordered_set;

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
    unordered_set<string> locationSet;
    for (auto [key, list1] : d) {
      string location = key;
      //if (!location.contains("\n")) {
        erase_if(location, [](unsigned char ch) {
          return isspace(ch);
        });
        if (!locationSet.contains(location)) {
          if (differ.contains(location)) {
            list<string> list2 = differ[location];
            list2.splice(list2.end(), list1);
            differ[location] = list2;
          } else {
            differ[location] = list1;
          }
          locationSet.insert(location);
        }
      //}
    }
  }
}
