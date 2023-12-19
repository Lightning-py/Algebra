#pragma once

#include <string> // std::string
#include <vector> // std::vector

namespace libs
{
  using line_type = std::string;
  using lines_type = std::vector<line_type>;

  auto parse(const line_type &command, char separator = ' ') -> lines_type;
  // output // 2023.12.12
  // getKey/getElems // 2023.12.12
  // algebra.hpp: dotProduct/crossProduct // 2023.12.12
}