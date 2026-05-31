#pragma once

#include <regex>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::regex;
using std::regex_match;
using std::unordered_set;
using std::list;
using std::unordered_map;
using std::string;

unordered_map<string, list<string>>& parseArguments(int argc, const char* argv[]);
