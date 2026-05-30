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

LocationParser::LocationParser(string& p) : status(0), value(""), fullPath(p) {}

void LocationParser::initProperty() {
  position = 0;
  line = 0;
  status = 0;
  key = "";
  value = "";
  chars.clear();
}

void LocationParser::showError(const string& errorMessage) {
  string blanks1 = "";
  cout << termcolor::bold << termcolor::grey << line << " " << termcolor::on_red << termcolor::bold << termcolor::white << this->lineText << termcolor::reset << endl;
  string blanks2 = "";
  for (int i = 0; i < position + getWidth(line) - 1; i += 1) {
    blanks2 += " ";
  }
  //if (line != 1) {
    shared_ptr<LocationLexer> locationLexer(new LocationLexer());
    //locationLexer->scanLine(beforeLineText);
    //vector<shared_ptr<LocationToken>> tokens = locationLexer->getTokens();
    //for (auto token: tokens) {
      //locationTemplate(*token);
    //}
  //}
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
            showError("The LocationParser internal state is abnormal.");
            exit(errorCode);
        }
      }
    }
  }
}


void LocationParser::dealChar(char c) {
  switch (status) {
    case 0:
      if (c == '%') {
        status = 1;
      } else {
        throw 1;
      }
      break;
    case 1:
      if (c == '*') {
        obtainKey();
        status = 2;
      } else {
        chars.push_back(c);
      }
      break;
    case 2:
      if (c == '%') {
        status = 3;
      } else {
        throw 2;
      }
      break;
    case 3:
      if (c == '[') {
        status = 4;
      } else {
        throw 3;
      }
      break;
    case 4:
      switch (c) {
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
    default:
      throw 4;
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
