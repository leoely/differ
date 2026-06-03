#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>
#include <exception>
#include <algorithm>
#include <cctype>
#include <termcolor/termcolor.hpp>
#include <LocationParser/LocationParser.hpp>
#include <DifferParser/DifferParser.hpp>
#include <VariableParser/VariableParser.hpp>
#include <DifferMerge/DifferMerge.hpp>
#include <LocationMerge/LocationMerge.hpp>
#include <VariableMerge/VariableMerge.hpp>
#include <FilePath/FilePath.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <generateHelp/generateHelp.hpp>

using std::vector;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;
using std::exception;
using std::erase_if;
using std::isspace;

namespace fs = std::filesystem;

void generate(vector<string>& arguments);
