#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>
#include <exception>
#include <termcolor/termcolor.hpp>
#include <argparse/argparse.hpp>
#include <LocationParser/LocationParser.hpp>
#include <DifferParser/DifferParser.hpp>
#include <help/help.hpp>

using std::vector;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;
using std::exception;

namespace fs = std::filesystem;

void generate(vector<string>& arguments);
