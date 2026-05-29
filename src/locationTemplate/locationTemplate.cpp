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
      cout << termcolor::color<23, 33, 200> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::ASTERISK:
      cout << termcolor::color<20, 240, 22> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::KEY:
      cout << termcolor::color<50, 50, 100> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::EQUAL:
      cout << termcolor::color<48, 230, 100> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::SQUARE_BRACKET:
      cout << termcolor::color<59, 20, 100> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::VALUE:
      cout << termcolor::color<245, 120, 10> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::AND:
      cout << termcolor::color<134, 120, 10> << token.elem << termcolor::reset;
      break;
  }
}
