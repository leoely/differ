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
#include <LocationTokenType/LocationTokenType.hpp>
#include <DifferTokenType/DifferTokenType.hpp>
#include <VariableTokenType/VariableTokenType.hpp>
#include <getWidth/getWidth.hpp>

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
    int locationSize = 0;
    int locationIndex = 0;;
    vector<shared_ptr<LocationToken>> locationTokens;
    for (const auto& locationOption: locationOptions) {
      shared_ptr<FilePath> filePath(new FilePath(locationOption, ".loc"));
      filePath->dealPath();
      string locationFilePathString = filePath->getFilePathString();
      shared_ptr<LocationLexer> locationLexer(new LocationLexer());
      ifstream locationFile(locationFilePathString);
      string line;
      while (getline(locationFile, line)) {
        locationLexer->scanLine(line, true);
        locationSize += 1;
      }
      vector<shared_ptr<LocationToken>> tokens = locationLexer->getTokens();
      locationTokens.insert(locationTokens.end(), tokens.begin(), tokens.end());
    }
    int locationWidth = getWidth(locationSize);
    for (const auto& locationToken : locationTokens) {
      LocationToken token = *locationToken;
      if (locationIndex == 0) {
        locationIndex += 1;
        int width = getWidth(locationIndex);
        string blank = "";
        for (int i = 0; i < locationWidth - width; i += 1) {
          blank += " ";
        }
        cout << termcolor::bold << termcolor::grey << locationIndex << " " << blank;
      }
      locationTemplate(token);
      if (token.type == LocationTokenType::LINE_BREAK && locationIndex != locationSize) {
        locationIndex += 1;
        int width = getWidth(locationIndex);
        string blank = "";
        for (int i = 0; i < locationWidth - width; i += 1) {
          blank += " ";
        }
        cout << termcolor::bold << termcolor::grey << locationIndex << " " << blank;
      }
    }
  }
}
