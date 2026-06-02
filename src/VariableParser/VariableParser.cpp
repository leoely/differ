#include <print>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <string>
#include <termcolor/termcolor.hpp>
#include <VariableLexer/VariableLexer.hpp>
#include <variableTemplate/variableTemplate.hpp>
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
    string key, value, fullPath;
    void dealChar(const char c);
    string lineText;
    string beforeLineText;
    unordered_map<string, string> variable;
    shared_ptr<VariableLexer> variableLexer;
  public:
    const unordered_map<string, string>& getVariable();
    explicit VariableParser(string& fullPath);
    void scanLine(const string& lineText);
    void showError(const string& errormessage);
};

VariableParser::VariableParser(string& fullPath) : status(0), key(""), value(""), fullPath(fullPath), variableLexer(new VariableLexer()) {}

void VariableParser::showError(const string& errorMessage) {
  int width1 = getWidth(line - 1);
  int width2 = getWidth(line);
  if (line != 1) {
    shared_ptr<VariableLexer> locationLexer(new VariableLexer());
    locationLexer->scanLine(beforeLineText, true);
    vector<shared_ptr<VariableToken>> tokens = locationLexer->getTokens();
    if (width2 == width1 + 1) {
      cout << termcolor::bold << termcolor::grey << line - 1 << "  ";
    } else {
      cout << termcolor::bold << termcolor::grey << line - 1 << " ";
    }
    for (auto token: tokens) {
      variableTemplate(*token);
    }
  }
  string blanks1 = "";
  cout << termcolor::bold << termcolor::grey << line << " " << termcolor::on_color<184, 31, 40> << termcolor::bold << termcolor::white << this->lineText << termcolor::reset << endl;
  string blanks2 = "";
  for (int i = 0; i < position + width2 - 1; i += 1) {
    blanks2 += " ";
  }
  cout << blanks2 << termcolor::reverse << termcolor::bold << "=^=" << termcolor::reset << termcolor::bold << " [Error] :: " << errorMessage << termcolor::reset << endl;
  cout << termcolor::dark << "[Type] :: "  << "Variable file;" << termcolor::reset << endl;
  cout << termcolor::dark << "[Path] :: \"" << fullPath << "\";" << termcolor::reset << endl;
  cout << termcolor::dark << "[Variable] :: Position: " << position << ", Line: " << line << ";" << termcolor::reset << endl;
}

void VariableParser::scanLine(const string &lineText) {
  position = 0;
  line += 1;
  this->beforeLineText = this->lineText;
  this->lineText = lineText;
  for (char c : lineText) {
    position += 1;
    if (c != ' ') {
      try {
        dealChar(c);
      } catch (int errorCode) {
        switch (errorCode) {
          case 1:
            showError("This position should be the character \"^\";");
            exit(errorCode);
          case 2:
            showError("This position should be the character \"(\";");
            exit(errorCode);
          case 3:
            showError("This position should be the character \"=\";");
            exit(errorCode);
          case 4:
            showError("This position should be the character \"\"\";");
            exit(errorCode);
        }
      }
    }
  }
  variableLexer->scanLine(beforeLineText, false);
}


void VariableParser::dealChar(char c) {
  switch (status) {
    case 0:
      if (c == '^') {
        status = 1;
      } else {
        throw 1;
      }
      break;
    case 1:
      if (c == '(') {
        status = 2;
      } else {
        throw 2;
      }
      break;
    case 2:
      if (c == ')') {
        key = obtainWord();
        status = 3;
      } else {
        chars.push_back(c);
      }
      break;
    case 3:
      if (c == '=') {
        status = 4;
      } else {
        throw 3;
      }
      break;
    case 4:
      if (c == '"') {
        status = 5;
      } else {
        throw 4;
      }
      break;
    case 5:
      if (c == '"') {
        value = obtainWord();
        variable[key] = value;
        status = 0;
      } else {
        chars.push_back(c);
      }
      break;
  }
}

const unordered_map<string, string>& VariableParser::getVariable() {
  return variable;
}
