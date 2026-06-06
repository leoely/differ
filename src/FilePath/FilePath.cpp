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

FilePath::FilePath(const string& pathString, const string& extension) : pathString(pathString), extension(extension) {}

string& FilePath::getFilePathString() {
  return filePathString;
}

void FilePath::dealPath() {
  try {
    fs::path filePath = pathString;
    if (filePath.is_absolute()) {
      filePath = pathString;
    } else {
      filePath = fs::absolute(filePath);
    }
    if (fs::exists(filePath) == false) {
      throw 1;
    }
    fs::path fileName = filePath.filename();
    string fileNameString(fileName.string());
    size_t lastIndex1 = fileNameString.find_last_of(".");
    string extensionString = fileNameString.substr(lastIndex1, fileNameString.size() - lastIndex1);
    if (extensionString != extension) {
      throw 2;
    }
    filePathString = filePath.string();
  } catch (int errorCode) {
    switch (errorCode) {
      case 1:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The path of the specified file \"" << extension << "\" does not exist." << termcolor::reset << endl;
        exit(errorCode);
      case 2:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The file must have the \"" << extension << "\" extension." << termcolor::reset << endl;
        exit(errorCode);
    }
  }
}
