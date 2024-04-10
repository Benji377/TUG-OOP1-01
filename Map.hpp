//---------------------------------------------------------------------------------------------------------------------
//
// The Map class represents the game board. It is a 2D grid of fields. The fields can be claimed by the players. The Map
// class is responsible for creating the game board, placing and moving chips and printing the game board.
// The Map class is created with a configuration file that defines the game board.
//
// Author: Benjamin Demetz
//---------------------------------------------------------------------------------------------------------------------
//

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

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Creates a 2D vector of fields from a configuration file. The configuration file defines the game board. The fields
  /// are created based on the characters in the configuration file. The characters are defined in the Field class.
  /// It is used as a helper function in the constructor of the Map class.
  ///
  /// @param config_path The path to the configuration file
  /// @param player_a The first player
  /// @param player_b The second player
  ///
  /// @return A 2D vector of fields
  //
  std::vector<std::vector<Field *>> createFieldMap(char *config_path, Player *player_a, Player *player_b) const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Creates a field based on a character. The character defines the type of the field. The field can be a normal field,
  /// a field from a player or a water field. It is used as a helper function in the createFieldMap function.
  ///
  /// @param field_char The character that defines the field (empty, player A, player B, water)
  /// @param player_a The first player
  /// @param player_b The second player
  ///
  /// @return A field
  //
  static Field *createField(char field_char, Player *player_a, Player *player_b);

public:
  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the number of columns of the game board.
  ///
  /// @param columns The number of columns
  //
  void setColumns(int columns);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the number of columns of the game board.
  ///
  /// @return The number of columns
  //
  [[nodiscard]] int getColumns() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the number of rows of the game board.
  ///
  /// @param rows The number of rows
  //
  void setRows(int rows);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the number of rows of the game board.
  ///
  /// @return The number of rows
  //
  [[nodiscard]] int getRows() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the fields of the game board.
  ///
  /// @param fields The fields of the game board
  //
  void setFields(std::vector<std::vector<Field *>> fields);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the fields of the game board.
  ///
  /// @return The fields of the game board
  //
  std::vector<std::vector<Field *>> getFields();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets whether the output is active or not. If the output is active, the game board is printed after each move.
  ///
  /// @param output_active Whether the output is active or not
  //
  void setIsOutputActive(bool output_active);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns whether the output is active or not. If the output is active, the game board is printed after each move.
  ///
  /// @return Whether the output is active or not
  //
  [[nodiscard]] bool getIsOutputActive() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Prints the game board. The game board is printed as a 2D grid. The fields are printed as characters.
  /// The characters are defined in the Field class. This function only does something if the output is active.
  //
  void printMap();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the amount of fields a player has claimed. The amount of fields a player has claimed is
  /// the amount of fields that have a chip of the player.
  ///
  /// @param player The player
  ///
  /// @return The amount of fields a player has claimed
  //
  int getFieldsPerPlayer(Player *player);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Places a chip on a field. The chip is placed on the field if the field is claimed by the same player performing
  /// the place operation. The chip is placed if the player has enough chips left and the field coordinates
  /// are valid. The player can't place a chip on the field of another player, outside the game borders or water.
  ///
  /// @param player The player that places the chip
  /// @param amount The amount of chips the player wants to place
  /// @param column The column of the field
  /// @param row The row of the field
  ///
  /// @return Whether the chip was placed successfully or not
  //
  bool placeChip(Player *player, int amount, int column, int row);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Moves a chip from one field to another. The chip is moved if the field it is moved from is claimed by
  /// the same player performing the move operation and the amount of chips is valid. The chip can be moved to
  /// a field claimed by the same player, another player or an empty field. The chip can't be moved to a field
  /// outside the game borders or water.
  ///
  /// @param player The player that moves the chip
  /// @param amount The amount of chips the player wants to move
  /// @param from_column The column of the field the chip is moved from
  /// @param from_row The row of the field the chip is moved from
  /// @param to_column The column of the field the chip is moved to
  /// @param to_row The row of the field the chip is moved to
  ///
  /// @return Whether the chip was moved successfully or not
  //
  bool moveChip(Player *player, int amount, int from_column, int from_row, int to_column, int to_row);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor of the Map class. The Map class represents the game board.
  ///
  /// @param config_path The path to the configuration file
  /// @param player_a The first player
  /// @param player_b The second player
  //
  Map(char *config_path, Player *player_a, Player *player_b);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy constructor of the Map class. The Map class represents the game board. Not used, therefore deleted.
  ///
  /// @param map The map to be copied
  //
  Map(const Map &) = delete;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor of the Map class. The Map class represents the game board.
  //
  ~Map();
};

#endif //MAP_HPP
