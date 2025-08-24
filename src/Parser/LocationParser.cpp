#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <Parser/Parser.hpp>

using namespace std;

class LocationParser : virtual public Parser {
  using Parser::Parser;
  private:
    int status;
    unordered_map<string, list<string>> location;
    list<string> fullList;
    string value;
    unordered_map<string, bool> fullHash;
    void appendValue();
    void dealChar(const char c);
  public:
    LocationParser();
    const unordered_map<string, list<string>> getLocation() const;
    void initProperty();
    const list<string> getFullList();
    void scanLine(const string &lineText);
};

LocationParser::LocationParser() : status(0), value("") {}

void LocationParser::initProperty() {
  position = 0;
  line = 0;
  status = 0;
  key = "";
  value = "";
  chars.clear();
}

void LocationParser::scanLine(const string &lineText) {
  position = 0;
  for (char c : lineText) {
    if (c != ' ') {
      try {
        dealChar(c);
      } catch (int errorCode) {
        switch (errorCode) {
          case 1:
            showError(lineText, "[Error] This position should be the character \"%\";");
            exit(errorCode);
          case 2:
            showError(lineText, "[Error] This position should be the character \"=\";");
            exit(errorCode);
          case 3:
            showError(lineText, "[Error] This position should be the character \"[\";");
            exit(errorCode);
          case 4:
            cout << "[Error] The LocationParser internal state is abnormal;" << endl;;
            exit(errorCode);
        }
      }
    }
    position += 1;
  }
  line += 1;
}


void LocationParser::dealChar(char c) {
  switch (status) {
    case 0:
      if (c == '%') {
        status = 1;
      } else {
        throw 1;
      }
      break;
    case 1:
      if (c == '*') {
        obtainKey();
        status = 2;
      } else {
        chars.push_back(c);
      }
      break;
    case 2:
      if (c == '=') {
        status = 3;
      } else {
        throw 2;
      }
      break;
    case 3:
      if (c == '[') {
        status = 4;
      } else {
        throw 3;
      }
      break;
    case 4:
      switch (c) {
        case '&':
          appendValue();
          chars.clear();
          value = "";
          break;
        case ']':
          appendValue();
          initProperty();
          break;
        default:
          chars.push_back(c);
      }
      break;
    default:
      throw 4;
  }
}

const unordered_map<string, list<string>> LocationParser::getLocation() const {
  if (location.size() == 0) {
    throw 5;
  } else {
    return location;
  }
}

void LocationParser::appendValue() {
  for (auto e: chars) {
    value.push_back(e);
  }
  if (location.find(key) == location.end()) {
    list<string> values = {value};
    location.emplace(key, values);
  } else {
    location.find(key)->second.push_back(value);
  }
  fullHash.emplace(value, true);
}

const list<string> LocationParser::getFullList() {
  if (fullHash.size() == 0) {
    throw 6;
  } else {
    if (fullList.size() == 0) {
      for (auto e: fullHash) {
        fullList.push_back(e.first);
      }
    }
    return fullList;
  }
}
