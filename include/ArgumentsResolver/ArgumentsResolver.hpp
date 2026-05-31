#pragma once

#include <iostream>
#include <regex>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::unordered_set;
using std::list;
using std::unordered_map;
using std::string;

class ArgumentsResolver {
  private:
    unordered_map<string, list<string>> argument;
    unordered_set<string> paramSet;
    int getType(string key);
    int status;
  public:
    unordered_map<string, list<string>>& parseArguments(list<string>& params);
    ArgumentsResolver();
};
