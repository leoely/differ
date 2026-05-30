#pragma once

#include <print>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <termcolor/termcolor.hpp>
#include <LocationLexer/LocationLexer.hpp>
#include <DifferLexer/DifferLexer.hpp>
#include <locationTemplate/locationTemplate.hpp>
#include <LocationToken/LocationToken.hpp>
#include <Parser/Parser.hpp>

using std::print;
using std::list;
using std::string;
using std::unordered_map;
using std::cout;
using std::endl;
using std::println;
using std::shared_ptr;

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
    string lineText;
    string beforeLineText;
  public:
    string fullPath;
    explicit LocationParser(string& p);
    const unordered_map<string, list<string>>& getLocation() const;
    void initProperty();
    const list<string>& getFullList();
    void scanLine(const string& lineText);
    void showError(const string& errormessage);
};
