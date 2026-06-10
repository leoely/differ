#include <print>
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
#include <ParametersResolver/ParametersResolver.hpp>
#include <previewHelp/previewHelp.hpp>

using std::println;
using std::vector;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::ifstream;
using std::exception;

void preview(vector<string>& parameters) {
  if (parameters.size() == 0) {
    previewHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "-h") {
    previewHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "--help") {
    previewHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ParametersResolver> parametersResolver(new ParametersResolver());
    unordered_map<string, vector<string>> parameter;
    try {
      parametersResolver->parseParameters(parameters);
      parameter = parametersResolver->getParameter();
    } catch (int errorCode) {
      previewHelp();
      exit(EXIT_FAILURE);
    }
    shared_ptr<LocationMerge> locationMerge(new LocationMerge());
    vector<string> locationOptions = parameter["l"];
    if (locationOptions.size() == 0) {
      cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " Without a \".loc\" file,it is impossible to generate the target file." << termcolor::reset << endl;
    }
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
    vector<string> variableOptions = parameter["v"];
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
    vector<string> diffOptions = parameter["d"];
    if (diffOptions.size() == 0) {
      cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " Without a \".diff\" file,it is impossible to generate the target file." << termcolor::reset << endl;
    }
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
    for (const auto& [key, list1] : differ) {
      cout << "\"" << termcolor::bold << key << termcolor::reset << "\"" << termcolor:: bold << ":" << termcolor::reset << endl;
      for (const auto& line : list1) {
        println("{}", line);
      }
    }
  }
}
