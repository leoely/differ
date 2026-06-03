#include <print>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <termcolor/termcolor.hpp>
#include <LocationLexer/LocationLexer.hpp>
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
    string key, fullPath;
    int status;
    unordered_map<string, list<string>> location;
    list<string> fullList;
    string value;
    unordered_map<string, bool> fullHash;
    void appendValue();
    void dealChar(const char c);
    string lineText;
    string beforeLineText;
    shared_ptr<LocationLexer> locationLexer;
  public:
    explicit LocationParser(string& p);
    const unordered_map<string, list<string>>& getLocation() const;
    void initProperty();
    const list<string>& getFullList();
    void scanLine(const string& lineText);
    void showError(const string& errormessage);
};

LocationParser::LocationParser(string& fullPath) : status(0), value(""), fullPath(fullPath), locationLexer(new LocationLexer) {}

void LocationParser::initProperty() {
  status = 0;
  key = "";
  value = "";
  chars.clear();
}

void LocationParser::showError(const string& errorMessage) {
  int width1 = getWidth(line - 1);
  int width2 = getWidth(line);
  if (line != 1) {
    locationLexer->scanLine(beforeLineText, true);
    vector<shared_ptr<LocationToken>> tokens = locationLexer->getTokens();
    if (width2 == width1 + 1) {
      cout << termcolor::bold << termcolor::grey << line - 1 << "  ";
    } else {
      cout << termcolor::bold << termcolor::grey << line - 1 << " ";
    }
    for (auto token: tokens) {
      locationTemplate(*token);
    }
  }
  string blanks1 = "";
  cout << termcolor::bold << termcolor::grey << line << " " << termcolor::on_color<184, 31, 40> << termcolor::bold << termcolor::white << this->lineText << termcolor::reset << endl;
  string blanks2 = "";
  for (int i = 0; i < position + width2 - 1; i += 1) {
    blanks2 += " ";
  }
  cout << blanks2 << termcolor::reverse << termcolor::bold << "=^=" << termcolor::reset << termcolor::bold << " [Error] :: " << errorMessage << termcolor::reset << endl;
  cout << termcolor::dark << "[Type] :: "  << "Location file;" << termcolor::reset << endl;
  cout << termcolor::dark << "[Path] :: \"" << fullPath << "\";" << termcolor::reset << endl;
  cout << termcolor::dark << "[Location] :: Position: " << position << ", Line: " << line << ";" << termcolor::reset << endl;
}

void LocationParser::scanLine(const string &lineText) {
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
            showError("This position should be the character \"%\";");
            exit(errorCode);
          case 2:
            showError("This position should be the character \"=\";");
            exit(errorCode);
          case 3:
            showError("This position should be the character \"[\";");
            exit(errorCode);
          case 4:
            showError("This position cannot be the charactor \"\\n\"");
            exit(errorCode);
        }
      }
    }
  }
  if (line > 1) {
    locationLexer->scanLine(this->beforeLineText + "\n", false);
  }
}


void LocationParser::dealChar(char c) {
  switch (status) {
    case 0:
      switch (c) {
        case '%':
          status = 1;
          break;
        default:
          throw 1;
      }
      break;
    case 1:
      switch (c) {
        case '\n':
          throw 4;
          break;
        case '*':
          key = obtainWord();
          status = 2;
          break;
        default:
          chars.push_back(c);
      }
      break;
    case 2:
      switch (c) {
        case '=':
          status = 3;
          break;
        default:
          throw 2;
      }
      break;
    case 3:
      switch (c) {
        case '[':
          status = 4;
          break;
        default:
          throw 3;
      }
      break;
    case 4:
      switch (c) {
        case '\n':
          throw 4;
          break;
        case '&':
          appendValue();
          chars.clear();
          value = "";
          break;
        case ']':
          appendValue();
          initProperty();
          break;
        default:
          chars.push_back(c);
      }
      break;
  }
}

const unordered_map<string, list<string>>& LocationParser::getLocation() const {
  if (location.size() == 0) {
    throw 5;
  } else {
    return location;
  }
}

void LocationParser::appendValue() {
  for (auto e: chars) {
    value.push_back(e);
  }
  if (location.find(key) == location.end()) {
    list<string> values = {value};
    location[key] = values;
  } else {
    location.find(key)->second.push_back(value);
  }
  fullHash[value] = true;
}

const list<string>& LocationParser::getFullList() {
  if (fullHash.size() == 0) {
    throw 6;
  } else {
    if (fullList.size() == 0) {
      for (auto e: fullHash) {
        fullList.push_back(e.first);
      }
    }
    return fullList;
  }
}
