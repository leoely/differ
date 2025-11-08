#include <list>
#include <unordered_map>
#include <string>

using namespace std;

string serializeStringListMap(unordered_map<string, list<string>> &stringListMap) {
  string string = "{";
  for (auto e : stringListMap) {
    string.append("'" + e.first + "':");
    string.append("[");
    for (auto it = e.second.begin(); it != e.second.end(); it++) {
      int index = distance(e.second.begin(), it);
      if (index != static_cast<int>(it->size() - 1)) {
        string.append("'" + *it + "',");
      } else {
        string.append("'" + *it + "'");
      }
    }
    string.append("]");
  }
  string.append("}");
  return string;
}
