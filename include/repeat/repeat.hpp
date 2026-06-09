#pragma once

#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <sago/platform_folders.h>
#include <termcolor/termcolor.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <clearHelp/clearHelp.hpp>

using std::to_string;
using std::from_chars;
using std::regex_match;
using std::regex;
using std::ios;
using std::size_t;
using std::count;
using std::istreambuf_iterator;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::stringstream;

namespace fs = std::filesystem;

void repeat(vector<string>& arguments);
