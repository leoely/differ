#pragma once

#include <iostream>
#include <regex>
#include <vector>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::unordered_set;
using std::vector;
using std::unordered_map;
using std::string;

class ArgumentsResolver {
  private:
    unordered_map<string, vector<string>> argument;
    unordered_set<string> paramSet;
    int getType(string key);
    int status;
  public:
    unordered_map<string, vector<string>>& parseArguments(vector<string>& params);
    ArgumentsResolver();
};
