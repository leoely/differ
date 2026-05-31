#pragma once

#include <print>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <string>
#include <termcolor/termcolor.hpp>
#include <VariableLexer/VariableLexer.hpp>
#include <locationTemplate/locationTemplate.hpp>
#include <VariableToken/VariableToken.hpp>
#include <Parser/Parser.hpp>

using std::print;
using std::string;
using std::unordered_map;
using std::cout;
using std::endl;
using std::println;
using std::shared_ptr;

class VariableParser : virtual public Parser {
  using Parser::Parser;
  private:
    int status;
    string value;
    void obtainValue();
    void dealChar(const char c);
    string lineText;
    string beforeLineText;
    unordered_map<string, string> variable;
  public:
    unordered_map<string, string>& getVariable();
    explicit VariableParser(string& p);
    void scanLine(const string& lineText);
    void showError(const string& errormessage);
};
