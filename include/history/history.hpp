#pragma once

#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sago/platform_folders.h>
#include <termcolor/termcolor.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <historyHelp/historyHelp.hpp>
#include <getWidth/getWidth.hpp>

using std::from_chars;
using std::regex_match;
using std::regex;
using std::ios;
using std::size_t;
using std::count;
using std::istreambuf_iterator;
using std::getline;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;

namespace fs = std::filesystem;

void history(vector<string>& arguments);
