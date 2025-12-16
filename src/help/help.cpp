#include <iostream>
#include <termcolor/termcolor.hpp>

using std::cout;
using std::endl;

void help() {
  cout << "" << endl;
  cout << "  ██████╗░██╗███████╗███████╗███████╗██████╗░" << endl;
  cout << "  ██╔══██╗██║██╔════╝██╔════╝██╔════╝██╔══██╗" << endl;
  cout << "  ██║░░██║██║█████╗░░█████╗░░█████╗░░██████╔╝" << endl;
  cout << "  ██║░░██║██║██╔══╝░░██╔══╝░░██╔══╝░░██╔══██╗" << endl;
  cout << "  ██████╔╝██║██║░░░░░██║░░░░░███████╗██║░░██║" << endl;
  cout << "  ╚═════╝░╚═╝╚═╝░░░░░╚═╝░░░░░╚══════╝╚═╝░░╚═╝" << endl;
  cout << "" << endl;
  cout << termcolor::bold << "Command line Prompt" << termcolor::reset << ":" << endl;
  cout << "  - generate Generate multiple difference files based on template files." << endl;
  cout << "  - validate Validate the syntax of file at different stages." << endl;
  cout << "" << endl;
}
