#include <fstream>
#include <vector>
#include <string>
#include <termcolor/termcolor.hpp>
#include <lookHelp/lookHelp.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <FilePath/FilePath.hpp>
#include <VariableLexer/VariableLexer.hpp>
#include <LocationLexer/LocationLexer.hpp>
#include <DifferLexer/DifferLexer.hpp>
#include <VariableParser/VariableParser.hpp>
#include <LocationParser/LocationParser.hpp>
#include <DifferParser/DifferParser.hpp>
#include <VariableToken/VariableToken.hpp>
#include <LocationToken/LocationToken.hpp>
#include <DifferToken/DifferToken.hpp>
#include <locationTemplate/locationTemplate.hpp>
#include <variableTemplate/variableTemplate.hpp>
#include <differTemplate/differTemplate.hpp>

using std::ifstream;
using std::string;
using std::vector;

void look(vector<string> arguments) {
  if (arguments.size() == 0) {
    lookHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-h") {
    lookHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    lookHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
    unordered_map<string, vector<string>> argument;
    try {
      argument = argumentsResolver->parseArguments(arguments);
    } catch (int errorCode) {
      lookHelp();
      exit(EXIT_FAILURE);
    }
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
    }
    for (const auto& locationOption: locationOptions) {
      shared_ptr<FilePath> filePath(new FilePath(locationOption, ".loc"));
      filePath->dealPath();
      string locationFilePathString = filePath->getFilePathString();
      shared_ptr<LocationLexer> locationLexer(new LocationLexer());
      ifstream locationFile(locationFilePathString);
      string line;
      while (getline(locationFile, line)) {
        locationLexer->scanLine(line, true);
      }
      vector<shared_ptr<LocationToken>> locationTokens = locationLexer->getTokens();
      for (const auto& locationToken : locationTokens) {
        locationTemplate(*locationToken);
      }
    }
  }
}
