#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <sago/platform_folders.h>
#include <termcolor/termcolor.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <locationHelp/locationHelp.hpp>
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
using std::stringstream;

namespace fs = std::filesystem;

void showLocations(int left, int right) {
  string documentPathString = sago::getDocumentsFolder();
  const fs::path documentPath = documentPathString;
  const fs::path homePath = documentPath.parent_path();
  fs::path differLocationsPath = homePath / ".differ_locations";
  if (!fs::exists(differLocationsPath)) {
    cout << termcolor::bold << "The locations is currently " << termcolor::reset <<  "[" << termcolor::bold << "empty" << termcolor::reset << "]" << termcolor::bold << ";" << termcolor::reset << endl;
  } else {
    if (left == -1 && right == -1) {
      ifstream differLocationsFile(differLocationsPath);
      size_t lineCount = count(
        istreambuf_iterator<char>(differLocationsFile),
        istreambuf_iterator<char>(),
        '\n'
      );
      differLocationsFile.clear();
      differLocationsFile.seekg(0, ios::beg);
      int width = getWidth(lineCount);
      string line;
      int count = 0;
      cout << "[" << termcolor::bold << "Location" << termcolor::reset << "]" << termcolor::reset << termcolor::bold << " Recoeds" << termcolor::reset << ":" << termcolor::reset << endl;
      while (getline(differLocationsFile, line)) {
        count += 1;
        int lineWidth = getWidth(count);
        string blanks = " ";
        for (int i = 0; i < width - lineWidth; i += 1) {
          blanks += " ";
        }
        cout << termcolor::color<150, 150, 150> << count << " " << termcolor::reset;
        stringstream ss(line);
        string location;
        while (getline(ss, location, ',')) {
          cout << "\"" << termcolor::color<150, 150, 150> << location << termcolor::reset << "\" ";
        }
        cout << endl;
      }
    } else if (right = -1) {
      ifstream differLocationsFile(differLocationsPath);
      size_t lineCount = count(
        istreambuf_iterator<char>(differLocationsFile),
        istreambuf_iterator<char>(),
        '\n'
      );
      differLocationsFile.clear();
      differLocationsFile.seekg(0, ios::beg);
      if (left < 1) {
        throw 5;
      }
      int width = getWidth(lineCount);
      string line;
      int count = 0;
      cout << "[" << termcolor::bold << "Location" << termcolor::reset << "]" << termcolor::reset << termcolor::bold << " Recoeds" << termcolor::reset << ":" << termcolor::reset << endl;
      while (getline(differLocationsFile, line)) {
        count += 1;
        if (count == left) {
          int lineWidth = getWidth(count);
          string blanks = " ";
          for (int i = 0; i < width - lineWidth; i += 1) {
            blanks += " ";
          }
          cout << termcolor::color<150, 150, 150> << count << " " << termcolor::reset;
          stringstream ss(line);
          string location;
          while (getline(ss, location, ',')) {
            cout << "\"" << termcolor::color<150, 150, 150> << location << termcolor::reset << "\" ";
          }
          cout << endl;
        }
      }
    } else {
      ifstream differLocationsFile(differLocationsPath);
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
      int width = getWidth(lineCount);
      string line;
      int count = 0;
      cout << "[" << termcolor::bold << "Location" << termcolor::reset << "]" << termcolor::reset << termcolor::bold << " Recoeds" << termcolor::reset << ":" << termcolor::reset << endl;
      while (getline(differLocationsFile, line)) {
        count += 1;
        if (count >= left && count <= right) {
          int lineWidth = getWidth(count);
          string blanks = " ";
          for (int i = 0; i < width - lineWidth; i += 1) {
            blanks += " ";
          }
          cout << termcolor::color<150, 150, 150> << count << " " << termcolor::reset;
          stringstream ss(line);
          string location;
          while (getline(ss, location, ',')) {
            cout << "\"" << termcolor::color<150, 150, 150> << location << termcolor::reset << "\" ";
          }
          cout << endl;
        }
      }
    }
  }
}

void location(vector<string>& arguments) {
  if (arguments.size() == 0) {
    locationHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-h") {
    locationHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    locationHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-a") {
    showLocations(-1, -1);
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--all") {
    showLocations(-1, -1);
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
    unordered_map<string, vector<string>> argument;
    try {
      argument = argumentsResolver->parseArguments(arguments);
    } catch (int errorCode) {
      locationHelp();
      exit(EXIT_FAILURE);
    }
    vector<string> pointerOptions = argument["p"];
    regex pattern("^\\^[0-9]+$");
    if (pointerOptions.size() == 1) {
      try {
        string pointerFullString = pointerOptions[0];
        if (!regex_match(pointerFullString, pattern)) {
          throw 1;
        }
        string pointerString = pointerFullString.substr(1, pointerFullString.size() - 1);
        int pointer = -1;
        from_chars(pointerString.data(), pointerString.data() + pointerString.size(), pointer);
        showLocations(pointer, pointer);
      } catch (int errorCode) {
        switch (errorCode) {
          case 1:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << "The format of the pointer should be \"^k\"." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 5:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << "The value of the pointer exceeds the boundary." << termcolor::reset << endl;
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
        showLocations(left, right);
      } catch (int errorCode) {
        switch (errorCode) {
          case 1:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << "The format of the left pointer should be \"^k\"." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 2:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << "The format of the left pointer should be \"^k\"." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 3:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << "The value of the left pointer exceeds the boundary." << termcolor::reset << endl;
            exit(errorCode);
            break;
          case 4:
            cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << "The value of the right pointer exceeds the boundary." << termcolor::reset << endl;
            exit(errorCode);
            break;
        }
      }
    } else {
      locationHelp();
      exit(EXIT_FAILURE);
    }
  }
}
