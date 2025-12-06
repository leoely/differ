#pragma once

#include <unordered_map>
#include <list>
#include <string>
#include <Parser/Parser.hpp>

using std::list;
using std::string;
using std::unordered_map;

class DifferParser : virtual public Parser {
  using Parser::Parser;
  private:
    int status;
    unordered_map<string, list<string>> differ;
    list<string> fullList;
    unordered_map<string, list<string>> location;
    bool dealChar(const char c, const string &lineText);
    void appendLine(const list<string> &stringList, const string &lineText);
  public:
    DifferParser(list<string> &fullList, unordered_map<string, list<string>> &location);
    const unordered_map<string, list<string>>& getDiffer() const;
    void initProperty();
    void scanLine(string &lineText);
};
