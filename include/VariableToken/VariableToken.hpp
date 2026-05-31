#pragma once

#include <string>
#include <VariableTokenType/VariableTokenType.hpp>

using std::string;

struct VariableToken {
  VariableTokenType type;
  string elem;
};
