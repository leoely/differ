#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <termcolor/termcolor.hpp>

namespace fs = std::filesystem;

using std::cout;
using std::endl;
using std::string;

class FilePath {
  private:
    string pathString, extension, filePathString;
  public:
    FilePath(const string& pathString, const string& extension);
    string& getFilePathString();
    void dealPath();
};
