//---------------------------------------------------------------------------------------------------------------------
//
// The Utils class contains some useful functions for use in other classes.
//
// Author: Tutors
//---------------------------------------------------------------------------------------------------------------------
//

#include "Utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

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

// https://stackoverflow.com/a/5207600
std::fstream& Utils::goToLine(std::fstream& file, int num){
  file.seekg(std::ios::beg);
  for(int i=0; i < num - 1; ++i){
    file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }
  return file;
}

std::string Utils::readConfigLine(char *config_path, int line_number) {
  std::string output;
  std::fstream config_file(config_path);
  goToLine(config_file, line_number);
  config_file >> output;
  //std::cin.get()
  return output;
}

bool Utils::isValidConfig(char *config_path) {
  std::fstream config_file(config_path);
  if(!config_file.is_open()){
    std::cout << "File not found" << std::endl;
    return false;
  }
  std::string magic = readConfigLine(config_path, 0);
  std::cout << "Magic number: " + magic;
  if (magic == "OOP\n") {
    return true;
  }
  return false;
}

std::vector<std::string> Utils::splitString(const std::string& string, const std::string& delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = string.find(delimiter, pos_start)) != std::string::npos) {
    token = string.substr (pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back (token);
  }

  res.push_back (string.substr (pos_start));
  return res;
}