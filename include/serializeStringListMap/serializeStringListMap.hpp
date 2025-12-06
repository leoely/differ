#pragma once

#include <list>
#include <unordered_map>
#include <string>

using std::list;
using std::unordered_map;
using std::string;

string serializeStringListMap(const unordered_map<string, list<string>> &stringListMap);
