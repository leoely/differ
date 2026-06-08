#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <sago/platform_folders.h>
#include <termcolor/termcolor.hpp>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <locationHelp/locationHelp.hpp>
#include <getWidth/getWidth.hpp>

using std::getline;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::stringstream;

namespace fs = std::filesystem;

void location(vector<string>& arguments);
