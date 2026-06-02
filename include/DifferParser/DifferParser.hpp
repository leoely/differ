#pragma once

#include <print>
#include <unordered_map>
#include <list>
#include <string>
#include <iostream>
#include <DifferLexer/DifferLexer.hpp>
#include <differTemplate/differTemplate.hpp>
#include <DifferToken/DifferToken.hpp>
#include <Parser/Parser.hpp>

using std::cout;
using std::endl;
using std::list;
using std::string;
using std::unordered_map;
using std::println;

class DifferParser : virtual public Parser {
  using Parser::Parser;
  private:
    string fullPath, singleLine, key, lineText, beforeLineText;
    int status;
    unordered_map<string, list<string>> differ;
    unordered_map<string, string> variable;
    list<string> fullList;
    unordered_map<string, list<string>> location;
    bool dealChar(const char c);
    void appendLine(const list<string>& stringList, const string& lineText);
    const string& dealTemplate(const string& lineText);
    shared_ptr<DifferLexer> differLexer;
  public:
    DifferParser(const string& fullPath, const list<string>& fullList, const unordered_map<string, list<string>>& location, const unordered_map<string, string>& variable);
    const unordered_map<string, list<string>>& getDiffer() const;
    void scan(const string& text);
    void scanLine(string& lineText);
    void showError(const string& errorMessage);
};
