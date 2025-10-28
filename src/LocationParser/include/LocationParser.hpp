#pragma once

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
