#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>
#include <DifferToken/DifferToken.hpp>
#include <DifferTokenType/DifferTokenType.hpp>

using std::print;
using std::println;
using std::cout;

void differTemplate(DifferToken& token) {
  switch (token.type) {
    case DifferTokenType::BLANK:
      print(" ");
      break;
    case DifferTokenType::LINE_BREAK:
      println("");
      break;
    case DifferTokenType::EQUAL:
      cout << termcolor::on_color<42, 123, 143> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::COLON:
      cout << termcolor::on_color<53, 62, 100> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::DIVIDER:
      cout << termcolor::on_color<232, 20, 100> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::CURLY_BRACE:
      cout << termcolor::on_color<123, 252, 42> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::PERCENTAGE:
      cout << termcolor::on_color<65, 134, 24> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::LOCATION:
      cout << termcolor::on_color<20, 60, 162> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::SINGLE:
      cout << termcolor::on_color<243, 122, 20> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::COMMENT:
      cout << termcolor::on_color<123, 235, 234> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::MULTIPLE:
      cout << termcolor::on_color<113, 135, 58> << token.elem << termcolor::reset;
      break;
  }
}
