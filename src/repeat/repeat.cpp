#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <sago/platform_folders.h>
#include <termcolor/termcolor.hpp>
#include <ParametersResolver/ParametersResolver.hpp>
#include <repeatHelp/repeatHelp.hpp>

using std::to_string;
using std::from_chars;
using std::regex_match;
using std::regex;
using std::ios;
using std::size_t;
using std::count;
using std::istreambuf_iterator;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::stringstream;

namespace fs = std::filesystem;

void repeatHistorys(int left, int right) {
  string documentPathString = sago::getDocumentsFolder();
  const fs::path documentPath = documentPathString;
  const fs::path homePath = documentPath.parent_path();
  fs::path differHistorysPath = homePath / ".differ_historys";
  if (fs::exists(differHistorysPath)) {
    if (right == -1) {
      ifstream differHistorysFile(differHistorysPath);
      size_t lineCount = count(
        istreambuf_iterator<char>(differHistorysFile),
        istreambuf_iterator<char>(),
        '\n'
      );
      if (left < 1) {
        throw 6;
      }
      if (left > lineCount) {
        throw 7;
      }
      differHistorysFile.clear();
      differHistorysFile.seekg(0, ios::beg);
      int count = 0;
      vector<string> lines;
      string line;
      while (getline(differHistorysFile, line)) {
        count += 1;
        if (count == left) {
          stringstream ss(line);
          string param;
          while (getline(ss, param, ',')) {
          }
        } else {
          lines.push_back(line);
        }
      }
      ofstream differHistorysFile1(differHistorysPath);
      for (const auto& line : lines) {
        differHistorysFile1 << line + "\n";
      }
      differHistorysFile1.close();
    } else {
      ifstream differHistorysFile(differHistorysPath);
      ofstream outputFile(differHistorysPath);
      size_t lineCount = count(
        istreambuf_iterator<char>(differHistorysFile),
        istreambuf_iterator<char>(),
        '\n'
      );
      if (left < 1) {
        throw 3;
      }
      if (right > lineCount) {
        throw 4;
      }
      differHistorysFile.clear();
      differHistorysFile.seekg(0, ios::beg);
      string line;
      vector<string> lines;
      int count = 0;
      while (getline(differHistorysFile, line)) {
        count += 1;
        if (count >= left && count <= right) {
          stringstream ss(line);
          string param;
          while (getline(ss, param, ',')) {
          }
        } else {
          lines.push_back(line);
        }
      }
      ofstream differHistorysFile1(differHistorysPath);
      for (const auto& line : lines) {
        differHistorysFile1 << line + "\n";
      }
      differHistorysFile1.close();
    }
  }
}


void repeat(vector<string>& parameters) {
  if (parameters.size() == 0) {
    repeatHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "-h") {
    repeatHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "--help") {
    repeatHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ParametersResolver> parametersResolver(new ParametersResolver());
    unordered_map<string, vector<string>> parameter;
    try {
      parameter = parametersResolver->parseParameters(parameters);
    } catch (int errorCode) {
      repeatHelp();
      exit(EXIT_FAILURE);
    }
    regex pattern("^\\^[0-9]+$");
    vector<string> pointerOptions = parameter["p"];
    vector<string> rangeOptions = parameter["r"];
    if (pointerOptions.size() >= 1) {
      if (rangeOptions.size() != 0) {
        repeatHelp();
        exit(EXIT_FAILURE);
      }
      try {
        for (const auto& pointerOption : pointerOptions) {
          string pointerFullString = pointerOption;
          if (!regex_match(pointerFullString, pattern)) {
            throw 5;
          }
          string pointerString = pointerFullString.substr(1, pointerFullString.size() - 1);
          int pointer = -1;
          from_chars(pointerString.data(), pointerString.data() + pointerString.size(), pointer);
          repeatHistorys(pointer, -1);
        }
      } catch (int errorCode) {
        switch (errorCode) {
          case 5:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The format of the pointer should be \"^k\"." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 6:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The value of the pointer exceeds the lower boundary." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 7:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The value of the pointer exceeds the upper boundary." << termcolor::reset << endl;
            exit(errorCode);
            break;
        }
      }
    } else if(rangeOptions.size() == 2) {
      if (rangeOptions.size() != 0) {
        repeatHelp();
        exit(EXIT_FAILURE);
      }
      try {
        string leftFullString = rangeOptions[0];
        string rightFullString = rangeOptions[1];
        if (!regex_match(leftFullString, pattern)) {
          throw 1;
        }
        if (!regex_match(rightFullString, pattern)) {
          throw 2;
        }
        string leftString = leftFullString.substr(1, leftFullString.size() - 1);
        string rightString = rightFullString.substr(1, rightFullString.size() - 1);
        int left = -1;
        int right = -1;
        from_chars(leftString.data(), leftString.data() + leftString.size(), left);
        from_chars(rightString.data(), rightString.data() + rightString.size(), right);
        repeatHistorys(left, right);
      } catch (int errorCode) {
        switch (errorCode) {
          case 1:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The format of the left pointer should be \"^k\"." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 2:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The format of the left pointer should be \"^k\"." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 3:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The value of the left pointer exceeds the boundary." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 4:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The value of the right pointer exceeds the boundary." << termcolor::reset << endl;
            exit(errorCode);
            break;
        }
      }
    } else {
      repeatHelp();
      exit(EXIT_FAILURE);
    }
  }
}
