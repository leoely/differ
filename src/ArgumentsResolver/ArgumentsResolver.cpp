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
    int status;
    static int getType(const string& key);
  public:
    unordered_map<string, vector<string>>& parseArguments(const vector<string>& params);
    ArgumentsResolver();
};

ArgumentsResolver::ArgumentsResolver() : status(0) {}

int ArgumentsResolver::getType(const string& key) {
  int type = 0;
  if (key == "v") {
    type = 1;
  }
  if (key == "variables") {
    type = 2;
  }
  if (key == "l") {
    type = 3;
  }
  if (key == "locations") {
    type = 4;
  }
  if (key == "d") {
    type = 5;
  }
  if (key == "differs") {
    type = 6;
  }
  if (key == "p") {
    type = 7;
  }
  if (key == "pointers") {
    type = 7;
  }
  return type;
}

unordered_map<string, vector<string>>& ArgumentsResolver::parseArguments(const vector<string>& params) {
  regex pattern1("^\\-[a-z]+$");
  regex pattern2("^\\-\\-[a-z]+$");
  status = 0;
  int type;
  string key;
  for (const auto &param : params) {
    switch (status) {
      case 0:
        if (regex_match(param, pattern1)) {
          key = param.substr(1);
          type = getType(key);
          status = 1;
        } else if (regex_match(param, pattern2)) {
          key = param.substr(2);
          type = getType(key);
          status = 1;
        } else {
          throw 1;
        }
        switch (type) {
          case 0:
            throw 2;
            break;
          case 1:
          case 2:
            if (paramSet.contains("v")) {
              throw 3;
            } else {
              paramSet.insert("v");
            }
            break;
          case 3:
          case 4:
            if (paramSet.contains("l")) {
              throw 3;
            } else {
              paramSet.insert("l");
            }
            break;
          case 5:
          case 6:
            if (paramSet.contains("d")) {
              throw 3;
            } else {
              paramSet.insert("d");
            }
            break;
          case 7:
          case 8:
            if (paramSet.contains("p")) {
              throw 3;
            } else {
              paramSet.insert("p");
            }
            break;
        }
        break;
      case 1:
        if (regex_match(param, pattern1)) {
          key = param.substr(1);
          status = 1;
          type = getType(key);
        } else if (regex_match(param, pattern2)) {
          key = param.substr(2);
          status = 1;
          type = getType(key);
        } else {
          switch (type) {
            case 0:
              throw 2;
              break;
            case 1:
            case 2:
              argument["v"].push_back(param);
              break;
            case 3:
            case 4:
              argument["l"].push_back(param);
              break;
            case 5:
            case 6:
              argument["d"].push_back(param);
              break;
            case 7:
            case 8:
              argument["p"].push_back(param);
              break;
          }
        }
        break;
    }
  }
  return argument;
}
