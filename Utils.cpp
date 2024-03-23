//---------------------------------------------------------------------------------------------------------------------
//
// The Utils class contains some useful functions for use in other classes.
//
// Author: Tutors
//---------------------------------------------------------------------------------------------------------------------
//

#include "Utils.hpp"

#include <algorithm>

bool Utils::decimalStringToInt(const std::string& str, int& number)
{
  size_t position = 0;

  try
  {
    number = std::stoul(str, &position, 10);
  }
  catch (std::exception&)
  {
    return false;
  }

  return position == str.length();
}
