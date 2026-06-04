#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <lookHelp/lookHelp.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <FilePath/FilePath.hpp>
#include <VariableLexer/VariableLexer.hpp>
#include <LocationLexer/LocationLexer.hpp>
#include <DifferLexer/DifferLexer.hpp>
#include <VariableParser/VariableParser.hpp>
#include <LocationParser/LocationParser.hpp>
#include <DifferParser/DifferParser.hpp>

using std::ifstream;
using std::string;
using std::vector;

void look(vector<string> arguments);
