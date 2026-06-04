#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>

using std::cout;
using std::endl;
using std::println;

void generateHelp() {
  cout << termcolor::bold << "Subcommand pattern" << termcolor::reset << "{" << termcolor::bold << "1" << termcolor::reset << "}" << termcolor::bold << ":" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  diff generate -d [d1] [d2] [...]" << termcolor::reset << endl;
  println("");
  cout << termcolor::bold << "Subcommand pattern" << termcolor::reset << "{" << termcolor::bold << "2" << termcolor::reset << "}" << termcolor::bold << ":" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  diff generate -l [l1] [l2] [...] - d [d1] [d2] [...]" << termcolor::reset << endl;
  println("");
  cout << termcolor::bold << "Subcommand pattern" << termcolor::reset << "{" << termcolor::bold << "3" << termcolor::reset << "}" << termcolor::bold << ":" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  diff generate -l [l1] [l2] [...] -v [v1] [v2] [...] -d [d1] [d2] [...]" << termcolor::reset << endl;
  println("");
  cout << "{" << termcolor::bold << "Short" << termcolor::reset << "}" << termcolor::bold << " and " << termcolor::reset << "{" << termcolor::bold << "long" << termcolor::reset << "}" << termcolor::bold << " flag comparsion" << termcolor::reset << ":" << endl;
  cout << termcolor::color<150, 150, 150> << "  -h --help" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  -v --variables" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  -l --locations" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  -d --differs" << termcolor::reset << endl;
  println("");
}
