#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>

using std::cout;
using std::endl;
using std::println;

void clearHelp() {
  cout << termcolor::bold << "Subcommand pattern" << termcolor::reset << "{" << termcolor::bold << "1" << termcolor::reset << "}" << termcolor::bold << ":" << termcolor::reset << endl;
  cout << termcolor::color<150, 150, 150> << "  diff clear" << termcolor::reset << endl;
  println();
}
