#include <iostream>
#include <vector>
#include <list>
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

using std::list;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;
using std::exception;

namespace fs = std::filesystem;

const string dealBlankLine(const string &textLine) {
  if (textLine == " ") {
    return "";
  } else {
    return textLine;
  }
}

void generate(const int argc, const char *argv[]) {
  argparse::ArgumentParser program("generate");
  program
    .add_argument("-f", "--file")
    .required()
    .help("specify the location of the differ template file.");
  try {
    program.parse_args(argc, argv);
  } catch (const exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }
  try {
    if (program.is_used("-f") || program.is_used("--file")) {
      string fOption = program.get<string>("-f");
      string fileOption = program.get<string>("--file");
      string differFilePathString;
      if (fOption.size() > 0) {
        differFilePathString = fOption;
      } else {
        differFilePathString = fileOption;
      }
      fs::path differFilePath = differFilePathString;
      if (differFilePath.is_absolute()) {
        differFilePath = differFilePathString;
      } else {
        differFilePath = fs::absolute(differFilePath);
      }
      if (fs::exists(differFilePath) == false) {
        throw 2;
      }
      fs::path differFileName = differFilePath.filename();
      string differFileNameString(differFileName.string());
      size_t lastIndex1 = differFileNameString.find_last_of(".");
      string differExtensionString = differFileNameString.substr(lastIndex1, differFileNameString.size() - lastIndex1);
      if (differExtensionString != ".differ") {
        throw 3;
      }
      fs::path parentPath = differFilePath.parent_path();
      string parentPathString(parentPath.string());
      string locFileNameString(differFileName.string());
      size_t lastIndex2 = locFileNameString.find_last_of(".");
      string locFileString = locFileNameString.substr(0, lastIndex2);
      fs::path locFilePath = fs::path(parentPathString) / (locFileString + ".loc");
      shared_ptr<LocationParser> locationParser(new LocationParser());
      if (fs::exists(locFilePath) == false) {
        throw 1;
      }
      ifstream file1(locFilePath);
      string str1;
      while (getline(file1, str1)) {
        locationParser->scanLine(str1);
      }
      unordered_map<string, list<string>> location = locationParser->getLocation();
      list<string> fullList = locationParser->getFullList();
      shared_ptr<DifferParser> differParser(new DifferParser(fullList, location));
      ifstream file2(differFilePathString);
      if (fs::exists(differFilePath) == false) {
        throw 2;
      }
      string str2;
      while (getline(file2, str2)) {
        differParser->scanLine(str2);
      }
      unordered_map<string, list<string>> differ = differParser->getDiffer();
      for (auto d: differ) {
        ofstream file;
        fs::path p = d.first;
        fs::path parentPath = p.parent_path();
        if (fs::exists(parentPath) == false) {
          fs::create_directories(parentPath);
        }
        file.open(d.first);
        for (auto it = d.second.begin(); it != d.second.end(); it++) {
          int index = distance(d.second.begin(), it);
          if (index == static_cast<int>(d.second.size() - 1)) {
            file << dealBlankLine(*it);
          } else {
            file << dealBlankLine(*it) << "\n";
          }
        }
        file.close();
      }
      cout << termcolor::green << termcolor::bold << "✔" << termcolor::reset << " Generate the target file according to the template file." << endl;
    } else {
      help();
      return;
    }
  } catch (int errorCode) {
    switch (errorCode) {
      case 1:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << " The path of the specified file \".loc\" does not exist." << endl;
        exit(errorCode);
      case 2:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << " The path of the specified file \".differ\" does not exist." << endl;
        exit(errorCode);
      case 3:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << " The extension of the differ file should be \".differ\"." << endl;
        exit(errorCode);
    }
  }
}
