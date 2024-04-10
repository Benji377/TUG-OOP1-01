#include "Map.hpp"
#include "Utils.hpp"
#include <utility>
#include <iostream>

Map::Map(char *config_path, Player *player_a, Player *player_b) {
  std::string dimensions = Utils::readConfigLine(config_path, 2);
  std::vector<std::string> split_dimensions = Utils::splitString(dimensions, "_");
  columns_ = stoi(split_dimensions.at(0));
  rows_ = stoi(split_dimensions.at(1));
  fields_ = createFieldMap(config_path, player_a, player_b);
  output_active_ = true;
}

int Map::getColumns() const {
  return columns_;
}

void Map::setColumns(int columns) {
  columns_ = columns;
}

int Map::getRows() const {
  return rows_;
}

void Map::setRows(int rows) {
  rows_ = rows;
}

std::vector<std::vector<Field *>> Map::getFields() {
  return fields_;
}

void Map::setFields(std::vector<std::vector<Field *>> fields) {
  fields_ = std::move(fields);
}

bool Map::getIsOutputActive() const {
  return output_active_;
}

void Map::setIsOutputActive(bool output_active) {
  output_active_ = output_active;
}

std::vector<std::vector<Field *>> Map::createFieldMap(char *config_path, Player *player_a, Player *player_b) const {
  std::string line;
  std::vector<std::vector<Field *>> fields(getRows(), std::vector<Field *>(getColumns()));
  for (int line_number = 0; line_number < getRows(); line_number++) {
    line = Utils::readConfigLine(config_path, line_number + 3);
    for (int field_number = 0; field_number < getColumns(); field_number++) {
      char field_char = line.at(field_number);
      fields[line_number][field_number] = createField(field_char, player_a, player_b);
    }
  }
  return fields;
}


Field *Map::createField(char field_char, Player *player_a, Player *player_b) {
  switch (field_char) {
    case 'a':
      return new Field(player_a, 1, false);
    case 'b':
      return new Field(player_b, 1, false);
    case '-':
      return new Field(nullptr, 0, true);
    default:
      return new Field(nullptr, 0, false);
  }
}

void Map::printMap() {
  if (!getIsOutputActive()) {
    return;
  }
  // Print first row
  for (int column_number = 0; column_number <= getColumns(); column_number++) {
    if (column_number == 0) {
      std::cout << "  ";
    } else {
      std::cout << "| " << column_number << " ";
    }
  }
  std::cout << "\n";
  for (int row_number = 0; row_number < getRows(); row_number++) {
    std::cout << row_number + 1 << " ";
    for (int column_number = 0; column_number < getColumns(); column_number++) {
      Field *field = getFields()[row_number][column_number];
      if (field->getPlayer() != nullptr) {
        std::cout << "|" << field->getPlayer()->getId() << " " << field->getChips();
      } else if (field->getIsWater()) {
        std::cout << "| ~ ";
      } else {
        std::cout << "|   ";
      }
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int Map::getFieldsPerPlayer(Player player) {
  int fields_per_player = 0;
  for (int row_number = 0; row_number < getRows(); row_number++) {
    for (int column_number = 0; column_number < getColumns(); column_number++) {
      Field *field = getFields()[row_number][column_number];
      if (field->getPlayer() != nullptr && field->getPlayer()->getId() == player.getId()) {
        fields_per_player++;
      }
    }
  }
  return fields_per_player;
}

bool Map::placeChip(Player *player, int amount, int column, int row) {
  if (column < 0 || column >= getColumns() || row < 0 || row >= getRows()) {
    return false;
  }
  Field *field = getFields()[row][column];

  if (field->getPlayer() == nullptr || field->getIsWater() || field->getPlayer()->getId() != player->getId()) {
    return false;
  }
  field->setChips(field->getChips() + amount);
  return true;
}

bool Map::moveChip(Player *player, int amount, int from_column, int from_row, int to_column, int to_row) {
  if (amount < 1) {
    std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
    return false;
  }
  if (from_column < 0 || from_column >= getColumns() || from_row < 0 || from_row >= getRows()) {
    std::cout << "[ERROR] Invalid origin!\n";
    return false;
  }
  // Player can only move chips from fields they own
  if (getFields()[from_row][from_column]->getPlayer() == nullptr ||
      getFields()[from_row][from_column]->getPlayer()->getId() != player->getId()) {
    std::cout << "[ERROR] Invalid origin!\n";
    return false;
  }
  if (to_column < 0 || to_column >= getColumns() || to_row < 0 || to_row >= getRows()) {
    std::cout << "[ERROR] Invalid destination!\n";
    return false;
  }
  Field *from_field = getFields()[from_row][from_column];
  Field *to_field = getFields()[to_row][to_column];
  if (from_field == to_field) {
    std::cout << "[ERROR] Invalid destination!\n";
    return false;
  }
  if (amount > from_field->getChips()) {
    std::cout << "[ERROR] Invalid amount! Must be a number <= chips on origin field!\n";
    return false;
  }
  // Player can only move chips to fields next to them
  if (abs(from_column - to_column) > 1 || abs(from_row - to_row) > 1) {
    std::cout << "[ERROR] Invalid destination!\n";
    return false;
  }
  if (to_field->getIsWater()) {
    std::cout << "[ERROR] Invalid destination!\n";
    return false;
  }
  if (to_field->getPlayer() == nullptr) {
    to_field->setPlayer(from_field->getPlayer());
    to_field->setChips(amount);
  } else if (to_field->getPlayer()->getId() == player->getId()) {
    to_field->setChips(to_field->getChips() + amount);
  } else {
    int new_destination_field_amount = to_field->getChips() + 1 - amount;
    if (new_destination_field_amount == 0) {
      to_field->setPlayer(nullptr);
    } else if (new_destination_field_amount < 0) {
      to_field->setChips(new_destination_field_amount * -1);
      to_field->setPlayer(from_field->getPlayer());
    } else {
      to_field->setChips(new_destination_field_amount);
    }
  }
  from_field->setChips(from_field->getChips() - amount);
  if (from_field->getChips() == 0) {
    from_field->setPlayer(nullptr);
  }
  return true;
}

Map::~Map() {
  for (int row_number = 0; row_number < getRows(); row_number++) {
    for (int column_number = 0; column_number < getColumns(); column_number++) {
      delete getFields()[row_number][column_number];
    }
  }
}