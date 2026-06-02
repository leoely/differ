#include <vector>
#include <string>
#include <help/help.hpp>
#include <generate/generate.hpp>
#include <validate/validate.hpp>

using std::vector;
using std::string;

int main(int argc, const char *argv[]) {
  if (argc == 1) {
    help();
    exit(EXIT_SUCCESS);
  }
  string argument1 = argv[1];
  if (argument1 == "--help") {
    help();
    exit(EXIT_SUCCESS);
  }
  vector<string> arguments;
  for (int i = 2; i < argc; i += 1) {
    string argument = argv[i];
    arguments.push_back(argument);
  }
  argc -= 2;
  if (argument1 == "generate") {
    generate(arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "validate") {
    validate(arguments);
    exit(EXIT_SUCCESS);
  } else {
    help();
    exit(EXIT_FAILURE);
  }
}
