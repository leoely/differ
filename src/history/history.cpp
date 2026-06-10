#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sago/platform_folders.h>
#include <termcolor/termcolor.hpp>
#include <ParametersResolver/ParametersResolver.hpp>
#include <historyHelp/historyHelp.hpp>
#include <getWidth/getWidth.hpp>

using std::from_chars;
using std::regex_match;
using std::regex;
using std::ios;
using std::size_t;
using std::count;
using std::istreambuf_iterator;
using std::getline;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;

namespace fs = std::filesystem;

void showHistorys(int left, int right) {
  string documentPathString = sago::getDocumentsFolder();
  const fs::path documentPath = documentPathString;
  const fs::path homePath = documentPath.parent_path();
  fs::path differHistorysPath = homePath / ".differ_historys";
  if (!fs::exists(differHistorysPath)) {
    cout << termcolor::bold << "The historys is currently " << termcolor::reset <<  "[" << termcolor::bold << "empty" << termcolor::reset << "]" << termcolor::bold << ";" << termcolor::reset << endl;
  } else {
    if (left == -1 && right == -1) {
      ifstream differHistorysFile(differHistorysPath);
      size_t lineCount = count(
        istreambuf_iterator<char>(differHistorysFile),
        istreambuf_iterator<char>(),
        '\n'
      );
      differHistorysFile.clear();
      differHistorysFile.seekg(0, ios::beg);
      int width = getWidth(lineCount);
      string line;
      int count = 0;
      while (getline(differHistorysFile, line)) {
        count += 1;
        int lineWidth = getWidth(count);
        string blanks = " ";
        for (int i = 0; i < width - lineWidth; i += 1) {
          blanks += " ";
        }
        cout << termcolor::color<150, 150, 150> << count << " " << termcolor::reset;
        cout << termcolor::on_white << termcolor::color<212, 87, 20> << "differ " << termcolor::reset << termcolor::on_white << termcolor::color<102, 69, 221> << line << termcolor::reset << endl;
      }
    } else if (right == -1) {
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
      int width = getWidth(lineCount);
      string line;
      int count = 0;
      while (getline(differHistorysFile, line)) {
        count += 1;
        if (count == left) {
          int lineWidth = getWidth(count);
          string blanks = " ";
          for (int i = 0; i < width - lineWidth; i += 1) {
            blanks += " ";
          }
          cout << termcolor::color<150, 150, 150> << count << " " << termcolor::reset;
          cout << termcolor::on_white << termcolor::color<212, 87, 20> << "differ " << termcolor::reset << termcolor::on_white << termcolor::color<102, 69, 221> << line << termcolor::reset << endl;
        }
      }
    } else {
      ifstream differHistorysFile(differHistorysPath);
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
      int width = getWidth(lineCount);
      string line;
      int count = 0;
      while (getline(differHistorysFile, line)) {
        count += 1;
        if (count >= left && count <= right) {
          int lineWidth = getWidth(count);
          string blanks = " ";
          for (int i = 0; i < width - lineWidth; i += 1) {
            blanks += " ";
          }
          cout << termcolor::color<150, 150, 150> << count << " " << termcolor::reset;
          cout << termcolor::on_white << termcolor::color<212, 87, 20> << "differ " << termcolor::reset << termcolor::on_white << termcolor::color<102, 69, 221> << line << termcolor::reset << endl;
        }
      }
    }
  }
}


void history(vector<string>& parameters) {
  if (parameters.size() == 0) {
    historyHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "-h") {
    historyHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "--help") {
    historyHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "-a") {
    showHistorys(-1, -1);
  } else if (parameters[0] == "--all") {
    showHistorys(-1, -1);
  } else {
    shared_ptr<ParametersResolver> parametersResolver(new ParametersResolver());
    unordered_map<string, vector<string>> parameter;
    try {
      parametersResolver->parseParameters(parameters);
      parameter = parametersResolver->getParameter();
    } catch (int errorCode) {
      historyHelp();
      exit(EXIT_FAILURE);
    }
    vector<string> pointerOptions = parameter["p"];
    regex pattern("^\\^[0-9]+$");
    if (pointerOptions.size() == 1) {
      try {
        string pointerFullString = pointerOptions[0];
        if (!regex_match(pointerFullString, pattern)) {
          throw 5;
        }
        string pointerString = pointerFullString.substr(1, pointerFullString.size() - 1);
        int pointer = -1;
        from_chars(pointerString.data(), pointerString.data() + pointerString.size(), pointer);
        showHistorys(pointer, -1);
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
    } else if(pointerOptions.size() == 2) {
      try {
        string leftFullString = pointerOptions[0];
        string rightFullString = pointerOptions[1];
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
        showHistorys(left, right);
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
      historyHelp();
      exit(EXIT_FAILURE);
    }
  }
}
