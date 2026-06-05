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
      cout << termcolor::bold << termcolor::color<205, 58, 168> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::KEY:
      cout << termcolor::bold << termcolor::color<184, 93, 205> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::ASTERISK:
      cout << termcolor::bold << termcolor::color<121, 196, 94> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::EQUAL:
      cout << termcolor::bold << termcolor::color<63, 205, 225> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::VALUE:
      cout << termcolor::bold << termcolor::color<215, 159, 103> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::SQUARE_BRACKET:
      cout << termcolor::bold << termcolor::color<139, 79, 188> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::AND:
      cout << termcolor::bold << termcolor::color<208, 99, 82> << token.elem << termcolor::reset;
      break;
  }
}
