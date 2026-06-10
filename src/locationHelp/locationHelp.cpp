#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>

using std::cout;
using std::endl;
using std::println;

void locationHelp() {
  cout << termcolor::bold << "Subcommand pattern" << termcolor::reset << "{" << termcolor::bold << "1" << termcolor::reset << "}" << termcolor::bold << ":" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  diff location -a" << termcolor::reset << endl;
  println("");
  cout << termcolor::bold << "Subcommand pattern" << termcolor::reset << "{" << termcolor::bold << "2" << termcolor::reset << "}" << termcolor::bold << ":" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  diff location -p [left] [right]" << termcolor::reset << endl;
  println("");
  cout << termcolor::bold << "Subcommand pattern" << termcolor::reset << "{" << termcolor::bold << "2" << termcolor::reset << "}" << termcolor::bold << ":" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  diff location -p [pointer]" << termcolor::reset << endl;
  println("");
  cout << "{" << termcolor::bold << "Short" << termcolor::reset << "}" << termcolor::bold << " and " << termcolor::reset << "{" << termcolor::bold << "long" << termcolor::reset << "}" << termcolor::bold << " flag comparsion" << termcolor::reset << ":" << endl;
  cout << termcolor::color<150, 150, 150> << "  -h --help" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  -a --all" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  -p --pointers" << termcolor::reset << endl;
  println("");
}
