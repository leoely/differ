#pragma once

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

void preview(vector<string>& parameters);
