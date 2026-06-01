#include <string>
#include <fstream>
#include <termcolor/termcolor.hpp>
#include <DifferParser/DifferParser.hpp>
#include <LocationParser/LocationParser.hpp>
#include <VariableParser/VariableParser.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <FilePath/FilePath.hpp>

using std::ifstream;
using std::shared_ptr;
using std::string;
using std::exit;
using std::getline;

namespace fs = std::filesystem;

void validate(list<string> arguments) {
  shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
  unordered_map<string, list<string>> argument = argumentsResolver->parseArguments(arguments);
  if (argument["d"].size() == 0) {
    list<string> locationOptions = argument["l"];
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
    list<string> variableOptions = argument["v"];
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
  }
}
