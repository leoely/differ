#pragma once

#include <list>
#include <unordered_map>
#include <string>

using namespace std;

string serializeStringListMap(unordered_map<string, list<string>> &stringListMap);
