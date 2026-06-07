#include <vector>
#include <string>
#include <clearHelp/clearHelp.hpp>

using std::string;
using std::vector;

void clear(vector<string>& arguments) {
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
  }
}
