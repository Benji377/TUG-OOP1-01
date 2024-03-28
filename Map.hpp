#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "Field.hpp"
#include "Player.hpp"

class Map {
private:
  int columns_;
  int rows_;
  std::vector<std::vector<Field*>> fields_;
  bool output_active_;
public:
  // Functions
  void setColumns(int columns);
  int getColumns();
  void setRows(int rows);
  int getRows();
  void setFields(std::vector<std::vector<Field*>> fields);
  std::vector<std::vector<Field*>> getFields();
  void setIsOutputActive(bool output_active);
  bool getIsOutputActive();
  // Constructors
  Map(char* config_path, Player* player_a, Player* player_b);
  Map(const Map&) = delete;
  ~Map() = default;
};

#endif //MAP_HPP
