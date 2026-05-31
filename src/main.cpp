#include <list>
#include <string>
#include <help/help.hpp>
#include <generate/generate.hpp>
#include <validate/validate.hpp>

using std::list;
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
  list<string> remainArguments;
  for (int i = 2; i < argc; i += 1) {
    string argument = argv[i];
    remainArguments.push_back(argument);
  }
  argc -= 2;
  if (argument1 == "generate") {
    //generate(remainArguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "validate") {
    validate(remainArguments);
    exit(EXIT_SUCCESS);
  } else {
    help();
    exit(EXIT_FAILURE);
  }
}
