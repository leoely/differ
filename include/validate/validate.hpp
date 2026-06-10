#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <termcolor/termcolor.hpp>
#include <DifferParser/DifferParser.hpp>
#include <LocationParser/LocationParser.hpp>
#include <VariableParser/VariableParser.hpp>
#include <ParametersResolver/ParametersResolver.hpp>
#include <FilePath/FilePath.hpp>
#include <LocationMerge/LocationMerge.hpp>
#include <VariableMerge/VariableMerge.hpp>
#include <validateHelp/validateHelp.hpp>

using std::vector;
using std::ifstream;
using std::shared_ptr;
using std::string;
using std::exit;
using std::getline;

namespace fs = std::filesystem;

void validate(vector<string>& arguments);
