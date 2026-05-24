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

namespace fs = std::filesystem;

void validate(const int argc, const char *argv[]) {
  argparse::ArgumentParser program("validate");
  auto &group = program.add_mutually_exclusive_group(true);
  group
    .add_argument("-d", "--differ")
    .help("check if the syntax of the differ file is correct.");
  group
    .add_argument("-l", "--location")
    .help("check if the location file syntax is correct.");
  try {
    program.parse_args(argc, argv);
  } catch (const exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }
  int status = 0;
  try {
    if (program.is_used("-d") || program.is_used("--differ")) {
      status = 1;
      string dOption = program.get<string>("-d");
      string differOption = program.get<string>("--differ");
      string differFilePathString;
      if (dOption.size() > 0) {
        differFilePathString = dOption;
      } else {
        differFilePathString = differOption;
      }
      fs::path differFilePath = differFilePathString;
      if (differFilePath.is_absolute()) {
        differFilePath = differFilePathString;
      } else {
        differFilePath = fs::absolute(differFilePath);
      }
      if (fs::exists(differFilePath) == false) {
        throw 1;
      }
      fs::path differFileName = differFilePath.filename();
      string differFileNameString(differFileName.string());
      size_t lastIndex1 = differFileNameString.find_last_of(".");
      string differExtensionString = differFileNameString.substr(lastIndex1, differFileNameString.size() - lastIndex1);
      if (differExtensionString != ".diff") {
        throw 2;
      }
      string locationFilePathString = differFilePathString;
      int differFilePathSize = differFilePathString.size();
      locationFilePathString.replace(differFilePathSize - 4, 5, "loc");
      fs::path locationFilePath = locationFilePathString;
      if (fs::exists(locationFilePath) == false) {
        throw 3;
      }
      shared_ptr<LocationParser> locationParser(new LocationParser());
      ifstream locationFile(locationFilePathString);
      string line1;
      while (getline(locationFile, line1)) {
        locationParser->scanLine(line1);
      }
      unordered_map<string, list<string>> location = locationParser->getLocation();
      list<string> fullList = locationParser->getFullList();
      ifstream differFile(differFilePathString);
      string line2;
      shared_ptr<DifferParser> differParser(new DifferParser(fullList, location));
      while (std::getline(differFile, line2)) {
        differParser->scanLine(line2);
      }
      cout << termcolor::green << termcolor::bold << "✔" << termcolor::reset << termcolor::bold << " Location and Diff file validation successful." << termcolor::reset << endl;
      exit(EXIT_SUCCESS);
    }
  } catch (int errorCode) {
    switch (errorCode) {
      case 1:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The location of the \".diff\" file doest not exist." << termcolor::reset << endl;
        exit(errorCode);
      case 2:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The file must have the \".diff\" extension." << termcolor::reset << endl;
        exit(errorCode);
      case 3:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " Validating the \".diff\" file requires a position file,the \".loc\" file located in the same directory as \".diff\" does not exist." << termcolor:: reset << endl;
        exit(errorCode);
    }
  }
  try {
    if (program.is_used("-l") || program.is_used("--location")) {
      shared_ptr<LocationParser> locationParser(new LocationParser());
      string lOption = program.get<string>("-l");
      string locationOption = program.get<string>("--location");
      string locationFilePathString;
      if (lOption.size() > 0) {
        locationFilePathString = lOption;
      } else {
        locationFilePathString = locationOption;
      }
      fs::path locationFilePath = locationFilePathString;
      if (locationFilePath.is_absolute()) {
        locationFilePath = locationFilePathString;
      } else {
        locationFilePath = fs::absolute(locationFilePath);
      }
      if (fs::exists(locationFilePath) == false) {
        throw 1;
      }
      fs::path locationFileName = locationFilePath.filename();
      string locationFileNameString(locationFileName.string());
      size_t lastIndex1 = locationFileNameString.find_last_of(".");
      string locationExtensionString = locationFileNameString.substr(lastIndex1, locationFileNameString.size() - lastIndex1);
      cout << locationExtensionString << endl;
      if (locationExtensionString != ".loc") {
        throw 2;
      }
      ifstream locationFile(locationFilePathString);
      string line;
      while (std::getline(locationFile, line)) {
        locationParser->scanLine(line);
      }
      cout << termcolor::green << termcolor::bold << "✔" << termcolor::reset << termcolor::bold << " Location file validation successful." << termcolor::reset << endl;
      exit(EXIT_SUCCESS);
    }
  } catch (int errorCode) {
    switch (errorCode) {
      case 1:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The path of the specified file \".loc\" does not exist." << termcolor::reset << endl;
        exit(errorCode);
      case 2:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << termcolor::bold << " The file must have the \".diff\" extension." << termcolor::reset << endl;
        exit(errorCode);
    }
  }
}
