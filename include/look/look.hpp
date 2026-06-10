#pragma once

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

void look(vector<string>& parameters);
