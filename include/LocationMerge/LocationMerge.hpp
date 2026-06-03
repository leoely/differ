#pragma once

#include <iostream>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <string>

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
    const list<string>& getFullList();
    unordered_map<string, list<string>> getLocation();
    void merge(vector<list<string>>& fullLists, vector<unordered_map<string, list<string>>>& locations);
};
