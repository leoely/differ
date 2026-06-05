#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>
#include <LocationToken/LocationToken.hpp>
#include <LocationTokenType/LocationTokenType.hpp>

using std::println;
using std::print;
using std::cout;

void locationTemplate(LocationToken& token) {
  switch (token.type) {
    case LocationTokenType::BLANK:
      print(" ");
      break;
    case LocationTokenType::LINE_BREAK:
      println("");
      break;
    case LocationTokenType::PERCENTAGE:
      cout << termcolor::bold << termcolor::color<169, 121, 98> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::KEY:
      cout << termcolor::bold << termcolor::color<154, 80, 139> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::ASTERISK:
      cout << termcolor::bold << termcolor::color<121, 156, 94> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::EQUAL:
      cout << termcolor::bold << termcolor::color<123, 115, 220> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::VALUE:
      cout << termcolor::bold << termcolor::color<175, 112, 93> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::SQUARE_BRACKET:
      cout << termcolor::bold << termcolor::color<129, 89, 118> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::AND:
      cout << termcolor::bold << termcolor::color<151, 65, 72> << token.elem << termcolor::reset;
      break;
  }
}
