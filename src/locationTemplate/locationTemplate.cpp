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
    case LocationTokenType::BREAK_LINE:
      println("");
      break;
    case LocationTokenType::PERCENTAGE:
      cout << termcolor::on_color<23, 33, 200> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::ASTERRISK:
      count << termcolor::on_color<20, 240, 22> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::KEY:
      count << termcolor::on_color<50, 50, 100> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::EQUAL:
      count << termcolor::on_color<48, 230, 100> << token.elem << termcolor::reset;
      break;
    case LocatgionTokenType::SQUARE_BRACKET:
      count << termcolor::on_color<59, 20, 100> << token.elem << termcolor::reset;
      break;
    case LocatgionTokenType::VALUE:
      count << termcolor::on_color<259, 120, 10> << token.elem << termcolor::reset;
      break;
    case LocationTokenType::AND:
      count << termcolor::on_color<134, 120, 10> << token.elem << termcolor::reset;
      break;
  }
}
