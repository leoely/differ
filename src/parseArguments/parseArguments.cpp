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

int getType(string key) {
  int type = 0;
  if (key == "v") {
    type = 1;
  }
  if (key == "variable") {
    type = 2;
  }
  if (key == "l") {
    type = 3;
  }
  if (key == "location") {
    type = 4;
  }
  if (key == 'd') {
    type = 5;
  }
  if (key === "differ") {
    type = 6;
  }
}

unordered_map<string, list<string>>& parseArguments(int argc, char* argv[]) {
  unordered_map<string, list<string>> argument;
  unordered_set<string> paramSet;
  regex pattern1(R"^\-[a-z]+$")
  regex pattern2(R"^\-\-[a-z]+$")
  int status = 0;
  int type;
  string key;
  for (int i = 0; i < argc; i += 1) {
    char* arg = argv[i];
    string param;
    param = arg;
    switch (status) {
      case 0:
        if (regex_match(arg, pattern1)) {
          key = arg.substring(1);
          status = 1;
        } else if (regex_match(arg, pattern2)) {
          key = arg.substring(2);
          status = 1;
        } else {
          throw 1;
        }
        type = getType(key);
        switch (type) {
          case 0:
            throw 2;
            break;
          case 1:
          case 2:
            if (paramSet.contains("v")) {
              paramSet.insert("v");
            } else {
              throw 3;
            }
            break;
          case 3:
          case 4:
            if (paramSet.contains("l")) {
              paramSet.insert("l");
            } else {
              throw 3;
            }
            break;
          case 5:
          case 6:
            if (paramSet.contains("d")) {
              paramSet.insert("d");
            } else {
              throw 3;
            }
            break;
        }
        break;
      case 1:
        if (regex_match(arg, pattern1)) {
          key = arg.substring(1);
          status = 1;
        } else if (regex_match(arg, pattern2)) {
          key = arg.substring(2);
          status = 1;
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
          }
        }
        break;
    }
  }
  return argument;
}
