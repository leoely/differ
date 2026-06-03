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
  string newLineText = lineText + "\n";
  for (char c : newLineText) {
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
          case 5:
            showError("This position cannot be the charactor \"\\n\";");
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
      switch (c) {
        case '\n':
          break;
        case '^':
          status = 1;
          break;
        default:
          throw 1;
      }
      break;
    case 1:
      switch (c) {
        case '(':
          status = 2;
          break;
        default:
          throw 2;
      }
      break;
    case 2:
      switch (c) {
        case '\n':
          throw 5;
        case ')':
          key = obtainWord();
          status = 3;
          break;
        default:
          chars.push_back(c);
      }
      break;
    case 3:
      switch (c) {
        case '=':
          status = 4;
          break;
        default:
          throw 3;
      }
      break;
    case 4:
      switch (c) {
        case '"':
          status = 5;
          break;
        default:
          throw 4;
      }
      break;
    case 5:
      switch (c) {
        case '\n':
          throw 5;
          break;
        case '"':
          value = obtainWord();
          variable[key] = value;
          status = 0;
          break;
        default:
          chars.push_back(c);
      }
      break;
  }
}

const unordered_map<string, string>& VariableParser::getVariable() {
  return variable;
}
