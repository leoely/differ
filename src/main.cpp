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
  string argv1 = argv[1];
  if (argv1 == "--help") {
    help();
    exit(EXIT_SUCCESS);
  }
  const char *remianArgv[argc - 1];
  for (int i = 1; i < argc; i += 1) {
    remainArgv[i - 1] = argv[i];
  }
  argc -= 1;
  if (argv1 == "generate") {
    generate(argc, remainArgv);
    exit(EXIT_SUCCESS);
  } else if (argv1 == "validate") {
    validate(argc, remainArgv);
    exit(EXIT_SUCCESS);
  } else {
    help();
    exit(EXIT_FAILURE);
  }
}
