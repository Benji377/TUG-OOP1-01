#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "Field.hpp"
#include "Player.hpp"

class Map {
private:
  int columns_;
  int rows_;
  std::vector<std::vector<Field *>> fields_;
  bool output_active_;

  std::vector<std::vector<Field *>> createFieldMap(char *config_path, Player *player_a, Player *player_b);
  static Field *createField(char field_char, Player *player_a, Player *player_b);

public:
  // Functions
  void setColumns(int columns);
  int getColumns();
  void setRows(int rows);
  int getRows();
  void setFields(std::vector<std::vector<Field *>> fields);
  std::vector<std::vector<Field *>> getFields();
  void setIsOutputActive(bool output_active);
  bool getIsOutputActive();
  void printMap();
  int getFieldsPerPlayer(Player player);
  bool placeChip(Player player, int amount, int column, int row);
  bool moveChip(Player player, int amount, int from_column, int from_row, int to_column, int to_row);

  // Constructors
  Map(char *config_path, Player *player_a, Player *player_b);
  Map(const Map &) = delete;
  ~Map();
};

#endif //MAP_HPP
