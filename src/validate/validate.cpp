#include <vector>
#include <string>
#include <fstream>
#include <termcolor/termcolor.hpp>
#include <DifferParser/DifferParser.hpp>
#include <LocationParser/LocationParser.hpp>
#include <VariableParser/VariableParser.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <FilePath/FilePath.hpp>
#include <validateHelp/validateHelp.hpp>

using std::vector;
using std::ifstream;
using std::shared_ptr;
using std::string;
using std::exit;
using std::getline;

namespace fs = std::filesystem;

void validate(vector<string> arguments) {
  if (arguments.size() == 0) {
    validateHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    validateHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
    unordered_map<string, vector<string>> argument = argumentsResolver->parseArguments(arguments);
    if (argument["d"].size() == 0) {
      vector<string> locationOptions = argument["l"];
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
        cout << termcolor::bold << "[Validation] :: " << termcolor::reset << termcolor::green << termcolor::bold << "✔" << termcolor::reset << " \"" << termcolor::color<145, 145, 145> << locationFilePathString << termcolor::reset << "\"" << termcolor::bold << ";" << termcolor::reset << endl;
      }
      vector<string> variableOptions = argument["v"];
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
        cout << termcolor::bold << "[Validation] :: " << termcolor::reset << termcolor::green << termcolor::bold << "✔" << termcolor::reset << " \"" << termcolor::color<145, 145, 145> << variableFilePathString << termcolor::reset << "\"" << termcolor::bold << ";" << termcolor::reset << endl;
      }
      exit(EXIT_SUCCESS);
    } else {
    }
  }
}
