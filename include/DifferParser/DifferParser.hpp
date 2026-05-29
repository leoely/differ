#pragma once

#include <print>
#include <unordered_map>
#include <list>
#include <string>
#include <iostream>
#include <Parser/Parser.hpp>

using std::list;
using std::string;
using std::unordered_map;
using std::println;

class DifferParser : virtual public Parser {
  using Parser::Parser;
  private:
    string lineText;
    string beforeLineText;
    int status;
    unordered_map<string, list<string>> differ;
    list<string> fullList;
    unordered_map<string, list<string>> location;
    bool dealChar(const char c, const string &lineText);
    void appendLine(const list<string>& stringList, const string& lineText);
  public:
    string fullPath;
    DifferParser(const string& p, const list<string>& f, const unordered_map<string, list<string>>& l);
    const unordered_map<string, list<string>>& getDiffer() const;
    void initProperty();
    void scan(const string& text);
    void scanLine(string& lineText);
    void showError(const string& errorMessage);
};
