#include "Map.hpp"
#include "Utils.hpp"
#include <utility>
#include <iostream>

Map::Map(char* config_path, Player* player_a, Player* player_b) {
  std::string dimensions = Utils::readConfigLine(config_path, 2);
  std::vector<std::string> split_dimensions = Utils::splitString(dimensions, "_");
  columns_ = stoi(split_dimensions.at(0));
  rows_ = stoi(split_dimensions.at(1));
  fields_ = createFieldMap(config_path, player_a, player_b);
  output_active_ = true;
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

//---------------------------------------------------------------------------------------------------------------------
///
/// This function creates a 2D vector of fields based on the config file. It reads the config file line by line and
/// creates a field object for each character in the line. The function is private and used by the constructor.
///
/// @param config_path The path to the config file
/// @param player_a The first player
/// @param player_b The second player
///
/// @return A 2D vector of fields parsed from the config file
//
std::vector<std::vector<Field*>> Map::createFieldMap(char* config_path, Player* player_a, Player* player_b) const {
  std::string line;
  std::vector<std::vector<Field*>> fields(rows_, std::vector<Field*> (columns_));
  for (int line_number = 0; line_number < rows_; line_number++) {
    line = Utils::readConfigLine(config_path, line_number+3);
    for (int field_number = 0; field_number < columns_; field_number++) {
      char field_char = line.at(field_number);
      // TODO: Free space after field has been deleted
      fields[line_number][field_number] = createField(field_char, player_a, player_b);
    }
  }
  return fields;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function creates a field object based on the character of the field in the config file. If the field is claimed
/// by a player, the player object is set. If the field is water, the is_water flag is set. If the field is empty, the
/// field is created without a player and without chips. The function is private and used by createFieldMap.
///
/// @param field_char The character of the field in the config file
/// @param player_a The first player
/// @param player_b The second player
///
/// @return a field object depending on the field_char
//
Field* Map::createField(char field_char, Player* player_a, Player* player_b) {
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

//---------------------------------------------------------------------------------------------------------------------
///
/// This function prints the map to the console. It iterates over all fields and prints the player id and the amount of
/// chips on the field. If the field is water, it prints a wave symbol. If the field is empty, it prints an empty space.
///
//
void Map::printMap() {
  if (!output_active_) {
    return;
  }
  // Print first row
  for (int column_number = 0; column_number <= columns_; column_number++) {
    if (column_number == 0) {
      std::cout << "  ";
    } else {
      std::cout << "| " << column_number << " ";
    }
  }
  std::cout << "\n";
  for (int row_number = 0; row_number < rows_; row_number++) {
    std::cout << row_number+1 << " ";
    for (int column_number = 0; column_number < columns_; column_number++) {
      Field* field = fields_[row_number][column_number];
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

//---------------------------------------------------------------------------------------------------------------------
///
/// This function counts the amount of fields a player has claimed by iterating over all fields and checking if
/// the player is the owner of the field.
///
/// @param player The player to count the fields for
///
/// @return the amount of fields the player has claimed
//
int Map::getFieldsPerPlayer(Player player) {
int fields_per_player = 0;
  for (int row_number = 0; row_number < rows_; row_number++) {
    for (int column_number = 0; column_number < columns_; column_number++) {
      Field* field = fields_[row_number][column_number];
      if (field->getPlayer() != nullptr && field->getPlayer()->getId() == player.getId()) {
        fields_per_player++;
      }
    }
  }
  return fields_per_player;
}