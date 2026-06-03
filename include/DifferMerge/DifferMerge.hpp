#pragma once

#include <unordered_map>
#include <string>
#include <list>
#include <vector>

using std::vector;
using std::unordered_map;
using std::string;
using std::list;

class DifferMerge {
  private:
    unordered_map<string, list<string>> differ;
  public:
    unordered_map<string, list<string>>& getDiffer();
    void merge(vector<unordered_map<string, list<string>>>& differs);
    DifferMerge();
};
