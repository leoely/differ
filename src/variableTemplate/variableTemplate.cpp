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
      cout << termcolor::bold << termcolor::color<239, 132, 26> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::COLON:
      cout << termcolor::bold << termcolor::color<123, 132, 26> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::EQUAL:
      cout << termcolor::bold << termcolor::color<203, 32, 126> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::CARET:
      cout << termcolor::bold << termcolor::color<231, 205, 26> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::KEY:
      cout << termcolor::bold << termcolor::color<231, 105, 26> << token.elem << termcolor::reset;
      break;
    case VariableTokenType::VALUE:
      cout << termcolor::bold << termcolor::color<231, 105, 226> << token.elem << termcolor::reset;
      break;
  }
}
