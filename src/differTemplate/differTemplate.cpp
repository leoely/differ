#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>
#include <DifferToken/DifferToken.hpp>
#include <DifferTokenType/DifferTokenType.hpp>

using std::print;
using std::println;
using std::cout;
using std::endl;

void differTemplate(DifferToken& token) {
  switch (token.type) {
    case DifferTokenType::BLANK:
      cout << token.elem;
      break;
    case DifferTokenType::LINE_BREAK:
      println("");
      break;
    case DifferTokenType::MULTIPLE:
      cout << termcolor::bold << termcolor::color<194, 215, 205> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::SINGLE:
      cout << termcolor::bold << termcolor::color<202, 198, 125> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::EQUAL:
      cout << termcolor:: bold << termcolor::color<205, 43, 93> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::CURLY_BRACE:
      cout << termcolor::bold << termcolor::color<78, 63, 211> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::PERCENTAGE:
      cout << termcolor::bold << termcolor::color<148, 43, 185> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::LOCATION:
      cout << termcolor::bold << termcolor::color<53, 143, 238> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::DIVIDER:
      cout << termcolor::bold << termcolor::color<202, 198, 125> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::HASHTAG:
      cout << termcolor::bold << termcolor::color<213, 125, 48> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::VARIABLE:
      cout << termcolor::bold << termcolor::color<204, 98, 58> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::COLON:
      cout << termcolor::bold << termcolor::color<125, 125, 125> << token.elem << termcolor::reset;
      break;
    case DifferTokenType::COMMENT:
      cout << termcolor::bold << termcolor::color<125, 125, 125> << token.elem << termcolor::reset;
      break;
  }
}
