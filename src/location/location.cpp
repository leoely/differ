#include <vector>
#include <string>
#include <locationHelp/locationHelp.hpp>

using std::string;
using std::vector;

void location(vector<string>& arguments) {
  if (arguments.size() == 0) {
    clearHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-h") {
    clearHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    clearHelp();
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
