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

DifferParser::DifferParser(const string& p, const list<string>& f, const unordered_map<string, list<string>>& l) : status(0), fullList(f), location(l), fullPath(p) {}

void DifferParser::showError(const string& errorMessage) {
  string blanks1 = "";
  cout << termcolor::bold << termcolor::grey << line << " " << termcolor::on_red << termcolor::bold << termcolor::white << this->lineText << termcolor::reset << endl;
  string blanks2 = "";
  for (int i = 0; i < position + getWidth(line) - 1; i += 1) {
    blanks2 += " ";
  }
  cout << blanks2 << termcolor::reverse << termcolor::bold << "=^=" << termcolor::reset << termcolor::bold << " :: [Error] " << errorMessage << termcolor::reset << endl;
  cout << termcolor::dark << "[Location] :: Position: " << position << " Line: " << line << ";" << termcolor::reset << endl;
}

void DifferParser::scanLine(string& lineText) {
  position = 0;
  line += 1;
  if (lineText == "") {
    lineText = " ";
  }
  this->beforeLineText = this->lineText;
  this->lineText = lineText;
  for (char c : lineText) {
    position += 1;
    try {
      if (dealChar(c, lineText) == true) {
        break;
      }
    } catch (int errorCode) {
      switch (errorCode) {
        case 1:
          showError("This position should be the character \"{\";");
          exit(errorCode);
        case 2:
          showError("This position should be the character \"%\";");
          exit(errorCode);
        case 3:
          showError("This position should be the character \"|\";");
          exit(errorCode);
        case 4:
          showError("This position should be the character \" \";");
          exit(errorCode);
        case 5:
          showError("This position should be the character \" \";");
          exit(errorCode);
      }
    }
  }
}

const unordered_map<string, list<string>>& DifferParser::getDiffer() const {
  return differ;
}

void DifferParser::initProperty() {
  line = 0;
  position = 0;
  status = 0;
}

bool DifferParser::dealChar(const char c, const string &lineText) {
  switch (status) {
    case 0:
      switch (c) {
        case '=':
          status = 2;
          break;
        case '"':
          status = 1;
          break;
        default:
          appendLine(fullList, lineText);
          status = 0;
          return true;
      }
      break;
    case 1:
      if (c == '=') {
        status = 8;
      }
      break;
    case 2:
      if (c == '{') {
        status = 3;
      } else {
        throw 1;
      }
      break;
    case 3:
      if (c == '%') {
        status = 4;
      } else {
        throw 2;
      }
      break;
    case 4:
      if (c == '}') {
        obtainKey();
        status = 5;
      } else {
        chars.push_back(c);
      }
      break;
    case 5:
      if (c == '|') {
        status = 6;
      } else {
        throw 3;
      }
      break;
    case 6:
      if (c == ' ') {
        if (location.find(key) != location.end()) {
          list<string> aloneList = location[key];
          string sub = lineText.substr(2, lineText.size() - 2);
          appendLine(aloneList, sub);
          status = 7;
          return true;
        } else {
          throw 4;
        }
      } else {
        throw 5;
      }
      break;
    case 7:
      if (c == '|') {
        status = 6;
      } else {
        status = 0;
        key = "";
        return dealChar(c, lineText);
      }
      break;
    case 8:
      string sub = lineText.substr(1, lineText.size() - 2);
      appendLine(fullList, sub);
      status = 0;
      break;
  }
  return false;
}

void DifferParser::appendLine(const list<string>& stringList, const string& lineText) {
  for (auto e : stringList) {
    if (differ.find(e) != differ.end()) {
      differ[e].push_back(lineText);
    } else {
      list<string> newList = {lineText};
      differ[e] = newList;
    }
  }
}
