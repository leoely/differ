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
    void appendLine(const list<string>& stringList, const string lineText);
    const string& dealTemplate(const string& lineText);
    shared_ptr<DifferLexer> differLexer;
  public:
    DifferParser(const string& fullPath, const list<string>& fullList, const unordered_map<string, list<string>>& location, const unordered_map<string, string>& variable);
    const unordered_map<string, list<string>>& getDiffer() const;
    void scan(const string& text);
    void scanLine(string& lineText);
    void showError(const string& errorMessage);
};

DifferParser::DifferParser(const string& fullPath, const list<string>& fullList, const unordered_map<string, list<string>>& location, const unordered_map<string, string>& variable) : status(0), fullList(fullList), location(location), fullPath(fullPath), variable(variable), differLexer(new DifferLexer()) {}

void DifferParser::showError(const string& errorMessage) {
  int width1 = getWidth(line - 1);
  int width2 = getWidth(line);
  if (line != 1) {
    differLexer->scanLine(beforeLineText, true);
    vector<shared_ptr<DifferToken>> tokens = differLexer->getTokens();
    if (width2 == width1 + 1) {
      cout << termcolor::bold << termcolor::grey << line - 1 << "  ";
    } else {
      cout << termcolor::bold << termcolor::grey << line - 1 << " ";
    }
    for (auto token: tokens) {
      differTemplate(*token);
    }
  }
  string blanks1 = "";
  cout << termcolor::bold << termcolor::grey << line << " " << termcolor::on_color<184, 31, 40> << termcolor::bold << termcolor::white << this->lineText << termcolor::reset << endl;
  string blanks2 = "";
  for (int i = 0; i < position + width2 - 1; i += 1) {
    blanks2 += " ";
  }
  cout << blanks2 << termcolor::reverse << termcolor::bold << "=^=" << termcolor::reset << termcolor::bold << " [Error] :: " << errorMessage << termcolor::reset << endl;
  cout << termcolor::dark << "[Type] :: "  << "Differ file;" << termcolor::reset << endl;
  cout << termcolor::dark << "[Path] :: \"" << fullPath << "\";" << termcolor::reset << endl;
  cout << termcolor::dark << "[Location] :: Position: " << position << ", Line: " << line << ";" << termcolor::reset << endl;
}

void DifferParser::scanLine(string& lineText) {
  position = 0;
  line += 1;
  if (lineText == "") {
    lineText = " ";
  }
  this->beforeLineText = this->lineText;
  this->lineText = lineText;
  string newLineText = lineText + "\n";
  for (char c : newLineText) {
    position += 1;
    try {
      dealChar(c);
    } catch (int errorCode) {
      switch (errorCode) {
        case 1:
          showError("This position should be the character \"{\";");
          exit(errorCode);
          break;
        case 2:
          showError("This position should be the character \"%\";");
          exit(errorCode);
          break;
        case 3:
          showError("This position should be the character \"|\";");
          exit(errorCode);
          break;
        case 4:
          showError("This position should be the character \" \";");
          exit(errorCode);
          break;
        case 5:
          showError("This position should be the character \" \";");
          exit(errorCode);
          break;
        case 6:
          showError("The corresponding location is not defined;");
          exit(errorCode);
          break;
        case 7:
          showError("The corresponding variable is not defined;");
          exit(errorCode);
          break;
      }
    }
  }
  if (line > 1) {
    differLexer->scanLine(this->beforeLineText, false);
  }
}

const unordered_map<string, list<string>>& DifferParser::getDiffer() const {
  return differ;
}

bool DifferParser::dealChar(const char c) {
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
          singleLine = "";
          singleLine += c;
          status = 11;
      }
      break;
    case 1:
      switch (c) {
        case '\n':
          status = 0;
          break;
      }
      break;
    case 2:
      switch (c) {
        case '{':
          status = 3;
          break;
        default:
          throw 1;
      }
      break;
    case 3:
      switch (c) {
        case '%':
          status = 4;
          break;
        default:
          throw 2;
      }
      break;
    case 4:
      switch (c) {
        case '}':
          key = obtainWord();
          status = 5;
          break;
        default:
          chars.push_back(c);
      }
      break;
    case 5:
      switch (c) {
        case '\n':
          break;
        case '|':
          status = 6;
          break;
        default:
          throw 3;
      }
      break;
    case 6:
      switch (c) {
        case ' ':
          status = 8;
          break;
        default:
          throw 4;
      }
      break;
    case 7:
      switch (c) {
        case '|':
          status = 6;
          break;
        default:
          status = 0;
          key = "";
          return dealChar(c);
      }
      break;
    case 8:
      switch (c) {
        case '#':
          status = 9;
          break;
        case '\n':
          erase_if(key, [](unsigned char ch) {
            return isspace(ch);
          });
          if (location.contains(key)) {
            list<string> aloneList = location[key];
            appendLine(aloneList, singleLine);
            singleLine = "";
            status = 7;
          } else {
            throw 6;
          }
          break;
        default:
          singleLine += c;
      }
      break;
    case 9:
      switch (c) {
        case '{':
          status = 10;
          break;
        default:
          singleLine += c;
          status = 11;
      }
      break;
    case 10:
      if (c == '}') {
        key = obtainWord();
        if (variable.contains(key)) {
          singleLine += variable[key];
        } else {
          throw 7;
        }
        status = 11;
      } else {
        chars.push_back(c);
      }
      break;
    case 11:
      switch (c) {
        case '#':
          status = 12;
          break;
        case '\n':
          appendLine(fullList, singleLine);
          singleLine = "";
          status = 0;
          break;
        default:
          singleLine += c;
      }
      break;
    case 12:
      switch (c) {
        case '{':
          status = 10;
          break;
        default:
          singleLine += "#";
          singleLine += c;
          status = 11;
      }
      break;
  }
  return false;
}

void DifferParser::appendLine(const list<string>& stringList, const string lineText) {
  for (auto e : stringList) {
    if (differ.find(e) != differ.end()) {
      differ[e].push_back(lineText);
    } else {
      list<string> newList = {lineText};
      differ[e] = newList;
    }
  }
}
