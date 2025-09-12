#include <iostream>
#include <termcolor/termcolor.hpp>

using namespace std;

void help() {
  cout << "" << endl;
  cout << "  ██████╗░██╗███████╗███████╗███████╗██████╗░" << endl;
  cout << "  ██╔══██╗██║██╔════╝██╔════╝██╔════╝██╔══██╗" << endl;
  cout << "  ██║░░██║██║█████╗░░█████╗░░█████╗░░██████╔╝" << endl;
  cout << "  ██║░░██║██║██╔══╝░░██╔══╝░░██╔══╝░░██╔══██╗" << endl;
  cout << "  ██████╔╝██║██║░░░░░██║░░░░░███████╗██║░░██║" << endl;
  cout << "  ╚═════╝░╚═╝╚═╝░░░░░╚═╝░░░░░╚══════╝╚═╝░░╚═╝" << endl;
  cout << "" << endl;
  cout << termcolor::bold << "  Description:" << termcolor::reset << " Generate different target files based on differences and the same template files." << endl;
  cout << "" << endl;
  cout << termcolor::bold << "  Command Prompt:" << termcolor::reset << endl;
  cout << "  - " << termcolor::bold << "generate" << termcolor::reset << endl;
  cout << "  | " << termcolor::reset << "-" << termcolor::bold << "f" << termcolor::reset << ",--" << termcolor::bold << "file " << termcolor::reset << "[differFile]" << endl;
  cout << "" << endl;
}
