#include <vector>
#include <string>
#include <command/help.hpp>
#include <command/generate.hpp>

using namespace std;

int main(int argc, const char *argv[]) {
  if (argc == 1) {
    help();
    return 1;
  }
  string argv1 = argv[1];
  if (argv1 == "--help") {
    help();
    return 1;
  }
  vector<string> args;
  for (int i = 2; i < argc; i += 1) {
    string arg = argv[i];
    args.push_back(arg);
  }
  if (argv1 == "generate") {
    generate(args);
    return 1;
  }
}
