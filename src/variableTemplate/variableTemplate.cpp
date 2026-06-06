#include <print>
#include <iostream>
#include <termcolor/termcolor.hpp>
#include <VariableToken/VariableToken.hpp>
#include <VariableTokenType/VariableTokenType.hpp>

using std::println;
using std::print;
using std::cout;

void variableTemplate(VariableToken& token) {
  switch (token.type) {
    case VariableTokenType::BLANK:
      print(" ");
      break;
    case VariableTokenType::LINE_BREAK:
      println("");
      break;
    case VariableTokenType::BRACKET:
      cout << termcolor::bold << termcolor::color<229, 128, 26> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::COLON:
      cout << termcolor::bold << termcolor::color<43, 142, 236> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::EQUAL:
      cout << termcolor::bold << termcolor::color<213, 52, 136> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::CARET:
      cout << termcolor::bold << termcolor::color<221, 195, 26> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::KEY:
      cout << termcolor::bold << termcolor::color<221, 95, 26> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::VALUE:
      cout << termcolor::bold << termcolor::color<121, 195, 116> << token.elem << termcolor::reset;
      break;
  }
}
