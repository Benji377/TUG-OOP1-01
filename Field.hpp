//---------------------------------------------------------------------------------------------------------------------
//
// The Field class is used to represent a field on the game board. It contains a player, the amount of chips on
// the field and if the field is water or not. The class contains methods to set and get the player,
// chips and is_water_ variables.
// The class also contains a constructor, copy constructor, assignment operator and destructor.
//
// Author: Benjamin Demetz
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef FIELD_HP
#define FIELD_HP

#include "Player.hpp"

class Field {
private:
  Player *player_;
  int chips_;
  bool is_water_;
public:
  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the player of a field, basically the owner
  ///
  /// @param player The player to be set
  //
  void setPlayer(Player *player);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the player of a field
  ///
  /// @return The player of the field
  //
  Player *getPlayer();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the amount of chips on a field
  ///
  /// @param amount The amount of chips to be set
  //
  void setChips(int amount);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the amount of chips on a field
  ///
  /// @return The amount of chips on the field
  //
  [[nodiscard]] int getChips() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets if a field is water or not
  ///
  /// @param is_water The value to be set
  //
  void setIsWater(bool is_water);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns if a field is water or not
  ///
  /// @return The value of is_water_
  //
  [[nodiscard]] bool getIsWater() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for the Field class. Initializes the player, chips and is_water_ variables
  ///
  /// @param player The player to be set
  /// @param chips The amount of chips to be set
  /// @param is_water If the field is a water field or not
  //
  Field(Player *player, int chips, bool is_water);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy constructor for the Field class. Deletes the copy constructor
  ///
  /// @param Field The Field to be copied
  //
  Field(const Field &) = delete;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Assignment operator for the Field class. Uses the default assignment operator
  ///
  /// @param Field The Field to be assigned
  //
  Field &operator=(const Field &) = default;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for the Field class. Uses the default destructor
  //
  ~Field() = default;
};

#endif //FIELD_HP