#pragma once

#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>
#include <LocationParser/LocationParser.hpp>
#include <DifferParser/DifferParser.hpp>

using std::list;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;

void generate(const int argc, const char *argv[]);
