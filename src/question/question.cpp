#include <iostream>
#include <string>
#include <algorithm>
#include <termcolor/termcolor.hpp>

using std::tolower;
using std::transform;
using std::string;
using std::cout;
using std::endl;
using std::cin;

bool question(string content) {
  string answer;
  cout << termcolor::bold << content << termcolor::reset << "yes[" << termcolor::bold << "Y" << termcolor::reset << "]/no[" << termcolor::bold << "N" << termcolor::reset << "]?";
  cin >> answer;
  transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char c) {
    return tolower(c);
  });
  if (answer == "y") {
    return true;
  } else if (answer == "yes") {
    return true;
  } else {
    return false;
  }
}
