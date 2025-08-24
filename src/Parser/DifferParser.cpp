#include <unordered_map>
#include <list>
#include <string>
#include <Parser/Parser.hpp>

using namespace std;

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
    const unordered_map<string, list<string>> getDiffer() const;
    void initProperty();
    void scanLine(string &lineText);
};

DifferParser::DifferParser(list<string> &fullList, unordered_map<string, list<string>> &location) : status(0), fullList(fullList), location(location) {}

void DifferParser::scanLine(string &lineText) {
  position = 0;
  if (lineText == "") {
    lineText = " ";
  }
  for (char c : lineText) {
    try {
      if (dealChar(c, lineText) == true) {
        break;
      }
    } catch (int errorCode) {
      switch (errorCode) {
        case 1:
          showError(lineText, "[Error] This position should be the character \"{\";");
          exit(errorCode);
        case 2:
          showError(lineText, "[Error] This position should be the character \"%\";");
          exit(errorCode);
        case 3:
          showError(lineText, "[Error] This position should be the character \"|\";");
          exit(errorCode);
        case 4:
          showError(lineText, "[Error] This position should be the character \" \";");
          exit(errorCode);
        case 5:
          showError(lineText, "[Error] This position should be the character \" \";");
          exit(errorCode);
      }
    }
    position += 1;
  }
  line += 1;
}

const unordered_map<string, list<string>> DifferParser::getDiffer() const {
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
        if (location.contains(key) == true) {
          list<string> aloneList = location.find(key)->second;
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

void DifferParser::appendLine(const list<string> &stringList, const string &lineText) {
  for (auto e : stringList) {
    if (differ.contains(e) == true) {
      differ.find(e)->second.push_back(lineText);
    } else {
      list<string> newList = {lineText};
      differ.emplace(e, newList);
    }
  }
}
