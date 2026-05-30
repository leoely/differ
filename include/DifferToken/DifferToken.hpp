#pragma once

#include <string>
#include <DifferTokenType/DifferTokenType.hpp>

using std::string;

struct DifferToken {
  DifferTokenType type;
  string elem;
};
