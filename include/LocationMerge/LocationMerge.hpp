#pragma once

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
