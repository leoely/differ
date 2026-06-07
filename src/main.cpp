#include <vector>
#include <string>
#include <help/help.hpp>
#include <generate/generate.hpp>
#include <validate/validate.hpp>
#include <preview/preview.hpp>
#include <look/look.hpp>
//#include <clear/clear.hpp>

using std::vector;
using std::string;

int main(int argc, const char *argv[]) {
  if (argc == 1) {
    help();
    exit(EXIT_SUCCESS);
  }
  string argument1 = argv[1];
  if (argument1 == "-h") {
    help();
    exit(EXIT_SUCCESS);
  } else if (argument1 == "--help") {
    help();
    exit(EXIT_SUCCESS);
  } else if (argument1 == "-v") {
    cout << "v1.0.0" << endl;
  } else if (argument1 == "--version") {
    cout << "v1.0.0" << endl;
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
  } else if (argument1 == "look") {
    look(arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "preview") {
    preview(arguments);
    exit(EXIT_SUCCESS);
  //} else if (argument1 == "clear") {
    //clear(arguments);
    //exit(EXIT_SUCCESS);
  } else {
    help();
    exit(EXIT_FAILURE);
  }
}
