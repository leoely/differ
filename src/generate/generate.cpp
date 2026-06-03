#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>
#include <exception>
#include <termcolor/termcolor.hpp>
#include <LocationParser/LocationParser.hpp>
#include <DifferParser/DifferParser.hpp>
#include <VariableParser/VariableParser.hpp>
#include <DifferMerge/DifferMerge.hpp>
#include <LocationMerge/LocationMerge.hpp>
#include <VariableMerge/VariableMerge.hpp>
#include <FilePath/FilePath.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <generateHelp/generateHelp.hpp>

using std::vector;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;
using std::exception;

namespace fs = std::filesystem;

const string dealBlankLine(const string& textLine) {
  if (textLine == " ") {
    return "";
  } else {
    return textLine;
  }
}

void generate(vector<string>& arguments) {
  if (arguments.size() == 0) {
    generateHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-h") {
    generateHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    generateHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
    unordered_map<string, vector<string>> argument;
    try {
      argument = argumentsResolver->parseArguments(arguments);
    } catch (int errorCode) {
      generateHelp();
      exit(EXIT_FAILURE);
    }
    shared_ptr<LocationMerge> locationMerge(new LocationMerge());
    vector<string> locationOptions = argument["l"];
    vector<list<string>> fullLists;
    vector<unordered_map<string, list<string>>> locations;
    for (const auto& locationOption: locationOptions) {
      shared_ptr<FilePath> filePath(new FilePath(locationOption, ".loc"));
      filePath->dealPath();
      string locationFilePathString = filePath->getFilePathString();
      shared_ptr<LocationParser> locationParser(new LocationParser(locationFilePathString));
      ifstream locationFile(locationFilePathString);
      string line;
      while (getline(locationFile, line)) {
        locationParser->scanLine(line);
      }
      locations.push_back(locationParser->getLocation());
      fullLists.push_back(locationParser->getFullList());
    }
    locationMerge->merge(fullLists, locations);
    list<string> fullList = locationMerge->getFullList();
    unordered_map<string, list<string>> location = locationMerge->getLocation();

    shared_ptr<VariableMerge> variableMerge(new VariableMerge());
    vector<string> variableOptions = argument["v"];
    vector<unordered_map<string, string>> variables;
    for (const auto& variableOption: variableOptions) {
      shared_ptr<FilePath> filePath(new FilePath(variableOption, ".var"));
      filePath->dealPath();
      string variableFilePathString = filePath->getFilePathString();
      shared_ptr<VariableParser> variableParser(new VariableParser(variableFilePathString));
      ifstream variableFile(variableFilePathString);
      string line;
      while (getline(variableFile, line)) {
        variableParser->scanLine(line);
      }
      variables.push_back(variableParser->getVariable());
    }
    variableMerge->merge(variables);
    unordered_map<string, string> variable = variableMerge->getVariable();

    shared_ptr<DifferMerge> differMerge(new DifferMerge());
    vector<string> diffOptions = argument["d"];
    vector<unordered_map<string, list<string>>> differs;
    for (const auto& diffOption: diffOptions) {
      shared_ptr<FilePath> filePath(new FilePath(diffOption, ".diff"));
      filePath->dealPath();
      string differFilePathString = filePath->getFilePathString();
      shared_ptr<DifferParser> differParser(new DifferParser(differFilePathString, fullList, location, variable));
      ifstream differFile(differFilePathString);
      string line;
      while (getline(differFile, line)) {
        differParser->scanLine(line);
      }
      differs.push_back(differParser->getDiffer());
    }
    differMerge->merge(differs);
    unordered_map<string, list<string>> differ = differMerge->getDiffer();
    for (const auto& [key, list] : differ) {
      ofstream file;
      fs::path p = key;
      fs::path parentPath = p.parent_path();
      if (fs::exists(parentPath) == false) {
        fs::create_directories(parentPath);
      }
      file.open(key);
      for (const auto& lineText : list) {
        file << lineText << "\n";
      }
      file.close();
    }
    for (const auto& [key, value] : differ) {
      cout << termcolor::bold << "[Generate] :: " << termcolor::reset << termcolor::green << termcolor::bold << "✔" << termcolor::reset << " \"" << termcolor::color<145, 145, 145> << key << termcolor::reset << "\"" << termcolor::bold << ";" << termcolor::reset << endl;
    }
  }
}
