#pragma once

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

