#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <argparse/argparse.hpp>
#include <termcolor/termcolor.hpp>
#include <DifferParser/DifferParser.hpp>
#include <LocationParser/LocationParser.hpp>

using std::ifstream;
using std::exception;
using std::shared_ptr;
using std::string;
using std::exit;
using std::getline;

namespace fs = std::filesystem;

void validate(const int argc, const char *argv[]);
