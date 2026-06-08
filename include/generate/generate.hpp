#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>
#include <exception>
#include <sstream>
#include <unordered_set>
#include <sago/platform_folders.h>
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

using std::next;
using std::iter_swap;
using std::views::join_with;
using std::ios_base;
using std::vector;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;
using std::exception;
using std::getenv;
using std::unordered_set;
using std::stringstream;

namespace fs = std::filesystem;

void generate(vector<string>& arguments);
