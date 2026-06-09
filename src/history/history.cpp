#include <memory>
#include <vector>
#include <string>
#include <ArgumentsResolver/ArgumentsResolver.hpp>
#include <historyHelp/historyHelp.hpp>

using std::vector;
using std::string;
using std::shared_ptr;

void history(vector<string>& arguments) {
  if (arguments.size() == 0) {
    historyHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "-h") {
    historyHelp();
    exit(EXIT_SUCCESS);
  } else if (arguments[0] == "--help") {
    historyHelp();
    exit(EXIT_SUCCESS);
  } else {
    shared_ptr<ArgumentsResolver> argumentsResolver(new ArgumentsResolver());
    unordered_map<string, vector<string>> argument;
    try {
      argument = argumentsResolver->parseArguments(arguments);
    } catch (int errorCode) {
      historyHelp();
      exit(EXIT_FAILURE);
    }
  }
}
