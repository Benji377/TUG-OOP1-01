#include "Map.hpp"
#include "Utils.hpp"
#include <utility>

Map::Map(char *config_path, Player *player_a, Player *player_b) {
  std::string dimensions = Utils::readConfigLine(config_path, 1);
  std::vector<std::string> split_dimensions = Utils::splitString(dimensions, "_");
  columns_ = stoi(split_dimensions.at(0));
  rows_ = stoi(split_dimensions.at(1));
  // TODO loop trough the rest of the file and set the fields
}

int Map::getColumns() {
  return columns_;
}
void Map::setColumns(int columns) {
  columns_ = columns;
}

int Map::getRows() {
  return rows_;
}
void Map::setRows(int rows) {
  rows_ = rows;
}

std::vector<std::vector<Field*>> Map::getFields() {
  return fields_;
}
void Map::setFields(std::vector<std::vector<Field*>> fields) {
  fields_ = std::move(fields);
}

bool Map::getIsOutputActive() {
  return output_active_;
}
void Map::setIsOutputActive(bool output_active) {
  output_active_ = output_active;
}