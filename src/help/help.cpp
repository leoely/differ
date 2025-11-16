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
  cout << "  | " << termcolor::reset << "-" << termcolor::bold << "f" << termcolor::reset << ", --" << termcolor::bold << "file " << termcolor::reset << "[" << termcolor::bold << "differFile" << termcolor::reset << "] Specify the path to the differ template file." << endl;
  cout << "" << endl;
}
