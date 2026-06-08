#include <memory>
#include <vector>
#include <string>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <locationHelp/locationHelp.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

void location(vector<string>& arguments) {
  if (arguments.size() == 0) {
    locationHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-h") {
    locationHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    locationHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
    unordered_map<string, vector<string>> argument;
    try {
      argument = argumentsResolver->parseArguments(arguments);
    } catch (int errorCode) {
      locationHelp();
      exit(EXIT_FAILURE);
    }
  }
}
