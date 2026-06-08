#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <sago/platform_folders.h>
#include <termcolor/termcolor.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <locationHelp/locationHelp.hpp>
#include <getWidth/getWidth.hpp>

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
    ifstream differLocationsFile(differLocationsPath);
    string line;
    int count = 0;
    cout << "[" << termcolor::bold << "Location" << termcolor::reset << "]" << termcolor::bold << " Recoeds" << termcolor::reset << ":" << termcolor::reset << endl;
    while (getline(differLocationsFile, line)) {
      count += 1;
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
  }
}
