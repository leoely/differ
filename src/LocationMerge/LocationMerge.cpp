#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <string>
#include <termcolor/termcolor.hpp>

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::unordered_set;
using std::unordered_map;
using std::list;
using std::string;

class LocationMerge {
  private:
    list<string> fullList;
    unordered_map<string, list<string>> location;
  public:
    LocationMerge();
    list<string>& getFullList();
    unordered_map<string, list<string>>& getLocation();
    void merge(vector<list<string>>& fullLists, vector<unordered_map<string, list<string>>>& locations);
};

void LocationMerge::merge(vector<list<string>>& fullLists, vector<unordered_map<string, list<string>>>& locations) {
  fullList.clear();
  location.clear();
  shared_ptr<unordered_set<string>> locationSet(new unordered_set<string>());
  try {
    for (const auto& f : fullLists) {
      for (const auto& l : f) {
        if (locationSet->contains(l)) {
          throw 1;
        } else {
          fullList.push_back(l);
        }
      }
    }
  } catch (int errorCode) {
    cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The path of the specified file \".loc\" does not exist." << termcolor::reset << endl;
    exit(errorCode);
  }
  for (const auto& l : locations) {
    for (const auto& [key, value] : l) {
      location[key] = value;
    }
  }
}

LocationMerge::LocationMerge() {}

list<string>& LocationMerge::getFullList() {
  return fullList;
}

unordered_map<string, list<string>>& LocationMerge::getLocation() {
  return location;
}
