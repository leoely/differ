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

namespace fs = std::filesystem;

void validate(const int argc, const char *argv[]) {
  argparse::ArgumentParser program("validate");
  program
    .add_argument("-d", "--differ")
    .help("check if the syntax of the differ file is correct.");
  program
    .add_argument("-l", "--location")
    .help("check if the location file syntax is correct.");
  try {
    program.parse_args(argc, argv);
  } catch (const exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }
  try {
    if (program.is_used("-d") || program.is_used("--differ")) {
      shared_ptr<DifferParser> differParser(new DifferParser());
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
      if (differExtensionString != ".differ") {
        throw 2;
      }
      ifstream differFile(differFilePathString);
      string line;
      while (std::getline(differFile, line)) {
        std::cout << line << std::endl;
        differParser->scanLine(line);
      }
    }
  } catch (int errorCode) {
    switch (errorCode) {
      case 1:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << "The location of the differ file doest not exist." << endl;
        exit(errorCode);
      case 2:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << "The file must have the .differ extension." << endl;
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
      if (locationExtensionString != ".differ") {
        throw 2;
      }
      ifstream locationFile(locationFilePathString);
      string line;
      while (std::getline(locationFile, line)) {
        locationParser->scanLine(line);
      }
    }
  } catch (int errorCode) {
    switch (errorCode) {
      case 1:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << "" << endl;
        exit(errorCode);
      case 2:
        cout << termcolor::dark << "[" << termcolor::reset << termcolor::bold << "Error" << termcolor::reset << termcolor::dark << "]" << termcolor::reset << " The path of the specified file \".differ\" does not exist." << endl;
        exit(errorCode);
    }
  }
}
