#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <termcolor/termcolor.hpp>
#include <lookHelp/lookHelp.hpp>
#include <ParametersResolver/ParametersResolver.hpp>
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
#include <LocationMerge/LocationMerge.hpp>
#include <VariableMerge/VariableMerge.hpp>
#include <getWidth/getWidth.hpp>

using std::list;
using std::ifstream;
using std::string;
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;

void outputWithLineNumber(int& index, int lastWidth) {
  index += 1;
  int width = getWidth(index);
  string blank = "";
  for (int i = 0; i < lastWidth - width; i += 1) {
    blank += " ";
  }
  cout << termcolor::bold << termcolor::grey << index << " " << blank;
}

void look(vector<string>& parameters) {
  if (parameters.size() == 0) {
    lookHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "-h") {
    lookHelp();
    exit(EXIT_SUCCESS);
  } else if (parameters[0] == "--help") {
    lookHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ParametersResolver> parametersResolver(new ParametersResolver());
    unordered_map<string, vector<string>> parameter;
    try {
      parameter = parametersResolver->parseParameters(parameters);
    } catch (int errorCode) {
      lookHelp();
      exit(EXIT_FAILURE);
    }
    vector<list<string>> fullLists;
    vector<unordered_map<string, list<string>>> locations;
    vector<string> locationOptions = parameter["l"];
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
      fullLists.push_back(locationParser->getFullList());
      locations.push_back(locationParser->getLocation());
    }
    cout << "[" << termcolor::bold << "Merged" << termcolor::reset <<"]" << termcolor::bold << " Location File" << termcolor::reset << ":" << termcolor::reset << endl;
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
       outputWithLineNumber(locationIndex, locationWidth);
      }
      locationTemplate(token);
      if (token.type == LocationTokenType::LINE_BREAK && locationIndex != locationSize) {
        outputWithLineNumber(locationIndex, locationWidth);
      }
    }
    vector<unordered_map<string, string>> variables;
    vector<string> variableOptions = parameter["v"];
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
    int variableSize = 0;
    int variableIndex = 0;;
    cout << "[" << termcolor::bold << "Merged" << termcolor::reset <<"]" << termcolor::bold << " Variable File" << termcolor::reset << ":" << termcolor::reset << endl;
    vector<shared_ptr<VariableToken>> variableTokens;
    for (const auto& variableOption: variableOptions) {
      shared_ptr<FilePath> filePath(new FilePath(variableOption, ".var"));
      filePath->dealPath();
      string variableFilePathString = filePath->getFilePathString();
      shared_ptr<VariableLexer> variableLexer(new VariableLexer());
      ifstream variableFile(variableFilePathString);
      string line;
      while (getline(variableFile, line)) {
        variableLexer->scanLine(line, true);
        variableSize += 1;
      }
      vector<shared_ptr<VariableToken>> tokens = variableLexer->getTokens();
      variableTokens.insert(variableTokens.end(), tokens.begin(), tokens.end());
    }
    int variableWidth = getWidth(variableSize);
    for (const auto& variableToken : variableTokens) {
      VariableToken token = *variableToken;
      if (variableIndex == 0) {
       outputWithLineNumber(variableIndex, variableWidth);
      }
      variableTemplate(token);
      if (token.type == VariableTokenType::LINE_BREAK && variableIndex != variableSize) {
        outputWithLineNumber(variableIndex, variableWidth);
      }
    }
    shared_ptr<LocationMerge> locationMerge(new LocationMerge());
    shared_ptr<VariableMerge> variableMerge(new VariableMerge());
    locationMerge->merge(fullLists, locations);
    variableMerge->merge(variables);
    vector<string> differOptions = parameter["d"];
    for (const auto& differOption: differOptions) {
      shared_ptr<FilePath> filePath(new FilePath(differOption, ".diff"));
      filePath->dealPath();
      string differFilePathString = filePath->getFilePathString();
      shared_ptr<DifferParser> differParser(new DifferParser(differFilePathString, locationMerge->getFullList(), locationMerge->getLocation(), variableMerge->getVariable()));
      ifstream differFile(differFilePathString);
      string line;
      while (getline(differFile, line)) {
        differParser->scanLine(line);
      }
    }
    cout << "[" << termcolor::bold << "Merged" << termcolor::reset <<"]" << termcolor::bold << " Differ File" << termcolor::reset << ":" << termcolor::reset << endl;
    int differSize = 0;
    int differIndex = 0;;
    vector<shared_ptr<DifferToken>> differTokens;
    for (const auto& differOption: differOptions) {
      shared_ptr<FilePath> filePath(new FilePath(differOption, ".diff"));
      filePath->dealPath();
      string differFilePathString = filePath->getFilePathString();
      shared_ptr<DifferLexer> differLexer(new DifferLexer());
      ifstream differFile(differFilePathString);
      string line;
      while (getline(differFile, line)) {
        differLexer->scanLine(line, true);
        differSize += 1;
      }
      vector<shared_ptr<DifferToken>> tokens = differLexer->getTokens();
      differTokens.insert(differTokens.end(), tokens.begin(), tokens.end());
    }
    int differWidth = getWidth(differSize);
    for (const auto& differToken : differTokens) {
      DifferToken token = *differToken;
      if (differIndex == 0) {
       outputWithLineNumber(differIndex, differWidth);
      }
      differTemplate(token);
      if (token.type == DifferTokenType::LINE_BREAK && differIndex != differSize) {
        outputWithLineNumber(differIndex, differWidth);
      }
    }
  }
}
