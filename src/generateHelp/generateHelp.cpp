#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>

using std::cout;
using std::endl;
using std::println;

void generateHelp() {
  cout << termcolor::bold << "Subcommand pattern{1}" << termcolor::reset << ":" << endl;
  println("  diff generate -d [d1] [d2] [...]");
  println("");
  cout << termcolor::bold << "Subcommand pattern{2}" << termcolor::reset << ":" << endl;
  println("  diff generate -l [l1] [l2] [...] - d [d1] [d2] [...]");
  println("");
  cout << termcolor::bold << "Subcommand pattern{3}" << termcolor::reset << ":" << endl;
  println("  diff generate -l [l1] [l2] [...] -v [v1] [v2] [...] -d [d1] [d2] [...]");
  println("");
  cout << termcolor::bold << "Short and long flag comparsion" << termcolor::reset << ":" << endl;
  println("  -h --help");
  println("  -v --variables");
  println("  -l --locations");
  println("  -d --differs");
  println("");
}
