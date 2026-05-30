#pragma once

#include <string>
#include <LocationTokenType/LocationTokenType.hpp>

using std::string;

struct LocationToken {
  LocationTokenType type;
  string elem;
};
