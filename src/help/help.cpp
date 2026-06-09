#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>

using std::cout;
using std::endl;
using std::println;

void help() {
  println();
  println("  ██████╗░██╗███████╗███████╗███████╗██████╗░");
  println("  ██╔══██╗██║██╔════╝██╔════╝██╔════╝██╔══██╗");
  println("  ██║░░██║██║█████╗░░█████╗░░█████╗░░██████╔╝");
  println("  ██║░░██║██║██╔══╝░░██╔══╝░░██╔══╝░░██╔══██╗");
  println("  ██████╔╝██║██║░░░░░██║░░░░░███████╗██║░░██║");
  println("  ╚═════╝░╚═╝╚═╝░░░░░╚═╝░░░░░╚══════╝╚═╝░░╚═╝");
  println();
  cout << termcolor::bold << "Command line prompt" << termcolor::reset << ":" << endl;
  println("  differ [subcommand] [arguments...]");
  cout << termcolor::bold << "Subcommand list" << termcolor::reset << ":" << endl;
  println("  - generate Generate multiple difference files based on template files.");
  println("  - validate Validate the syntax of file at different stages.");
  println("  - preview  Preview the final generated file content via command line.");
  println("  - look     Look ths source files at different stages of merging.");
  println("  - location View the location record of previously generated files.");
  println("  - clear    Clear previously generated target files.");
  println();
}
