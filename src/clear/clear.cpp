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
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <question/question.hpp>
#include <clearHelp/clearHelp.hpp>

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

void clearLocations(int left, int right) {
  string documentPathString = sago::getDocumentsFolder();
  const fs::path documentPath = documentPathString;
  const fs::path homePath = documentPath.parent_path();
  fs::path differLocationsPath = homePath / ".differ_locations";
  if (fs::exists(differLocationsPath)) {
    if (left == -1 && right == -1) {
      bool ans = question("Are you sure you want to delete all the files pointed to.");
      if (ans == false) {
        return;
      }
      ifstream differLocationsFile(differLocationsPath);
      string line;
      while (getline(differLocationsFile, line)) {
        stringstream ss(line);
        string location;
        while (getline(ss, location, ',')) {
          fs::path locationPath = location;
          fs::remove(locationPath);
        }
      }
      ofstream differLocationsFile1(differLocationsPath);
      differLocationsFile1.close();
    } else if (right == -1) {
      bool ans = question("Are you sure you want to delete all the files pointed to.");
      if (ans == false) {
        return;
      }
      ifstream differLocationsFile(differLocationsPath);
      size_t lineCount = count(
        istreambuf_iterator<char>(differLocationsFile),
        istreambuf_iterator<char>(),
        '\n'
      );
      differLocationsFile.clear();
      differLocationsFile.seekg(0, ios::beg);
      if (left < 1) {
        throw 6;
      }
      if (left > lineCount) {
        throw 7;
      }
      int count = 0;
      vector<string> lines;
      string line;
      while (getline(differLocationsFile, line)) {
        count += 1;
        if (count == left) {
          stringstream ss(line);
          string location;
          while (getline(ss, location, ',')) {
            fs::path locationPath = location;
            fs::remove(locationPath);
          }
        } else {
          lines.push_back(line);
        }
      }
      ofstream differLocationsFile1(differLocationsPath);
      for (const auto& line : lines) {
        differLocationsFile1 << line + "\n";
      }
      differLocationsFile1.close();
    } else {
      bool ans = question("Are you sure you want to delete all the files pointed to.");
      if (ans == false) {
        return;
      }
      ifstream differLocationsFile(differLocationsPath);
      ofstream outputFile(differLocationsPath);
      size_t lineCount = count(
        istreambuf_iterator<char>(differLocationsFile),
        istreambuf_iterator<char>(),
        '\n'
      );
      differLocationsFile.clear();
      differLocationsFile.seekg(0, ios::beg);
      if (left < 1) {
        throw 3;
      }
      if (right > lineCount) {
        throw 4;
      }
      string line;
      vector<string> lines;
      int count = 0;
      while (getline(differLocationsFile, line)) {
        count += 1;
        if (count >= left && count <= right) {
          stringstream ss(line);
          string location;
          while (getline(ss, location, ',')) {
            fs::path locationPath = location;
            fs::remove(locationPath);
          }
        } else {
          lines.push_back(line);
        }
      }
      ofstream differLocationsFile1(differLocationsPath);
      for (const auto& line : lines) {
        differLocationsFile1 << line + "\n";
      }
      differLocationsFile1.close();
    }
  }
}

void clear(vector<string>& arguments) {
  if (arguments.size() == 0) {
    clearHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-h") {
    clearHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    clearHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-a") {
    clearLocations(-1, -1);
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--all") {
    clearLocations(-1, -1);
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
    unordered_map<string, vector<string>> argument;
    try {
      argument = argumentsResolver->parseArguments(arguments);
    } catch (int errorCode) {
      clearHelp();
      exit(EXIT_FAILURE);
    }
    vector<string> pointerOptions = argument["p"];
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
        clearLocations(pointer, -1);
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
        clearLocations(left, right);
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
      clearHelp();
      exit(EXIT_FAILURE);
    }
  }
}
