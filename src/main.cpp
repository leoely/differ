#include <vector>
#include <string>
#include <command/help.hpp>
#include <command/generate.hpp>

using namespace std;

int main(int argc, const char *argv[]) {
  if (argc == 1) {
    help();
    return 0;
  }
  string argv1 = argv[1];
  if (argv1 == "--help") {
    help();
    return 0;
  }
  const char *subArgv[argc - 1];
  for (int i = 1; i < argc; i += 1) {
    subArgv[i - 1] = argv[i];
  }
  argc -= 1;
  if (argv1 == "generate") {
    generate(argc, subArgv);
    return 0;
  }
}
