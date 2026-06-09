#include <vector>
#include <string>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <repeatHelp/repeatHelp.hpp>

using std::vector;
using std::string;
using std::shared_ptr;

void repeat(vector<string>& arguments) {
  if (arguments.size() == 0) {
    repeatHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-h") {
    repeatHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    repeatHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
    unordered_map<string, vector<string>> argument;
    try {
      argument = argumentsResolver->parseArguments(arguments);
    } catch (int errorCode) {
      repeatHelp();
      exit(EXIT_FAILURE);
    }
  }
}
