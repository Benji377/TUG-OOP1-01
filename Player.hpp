//---------------------------------------------------------------------------------------------------------------------
//
// The Player class represents a player in the game. It has an id, a number of chips and a boolean to check if
// the player has passed. The class also has functions to get and set the values of the member variables and
// a function to print the player's information.
//
// Author: Benjamin Demetz
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
private:
  char id_;
  int chips_;
  bool has_passed_;
public:
  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the id of the player. Either A or B. Uses [[nodiscard]] to indicate that the return value should be used.
  ///
  /// @return The id of the player
  //
  [[nodiscard]] char getId() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the id of the player. Either A or B. The restriction is not checked, but the game only uses A and B.
  ///
  /// @param id The id to be set
  //
  void setId(char id);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the amount of chips the player has. Uses [[nodiscard]] to indicate that the return value should be used.
  ///
  /// @return The amount of chips the player has
  //
  [[nodiscard]] int getChips() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the amount of chips the player has.
  ///
  /// @param chips The amount of chips to be set
  //
  void setChips(int chips);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns whether the player has passed or not. Uses [[nodiscard]] to indicate that the return value should be used.
  ///
  /// @return Whether the player has passed or not
  //
  [[nodiscard]] bool getHasPassed() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets whether the player has passed the current game phase or not.
  ///
  /// @param has_passed Whether the player has passed or not
  //
  void setHasPassed(bool has_passed);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Prints the player's information. The information includes the player's id, the amount of chips the player has and
  /// the amount of fields the player has claimed.
  ///
  /// @param claimed_fields The amount of fields the player has claimed, provided from the Map class
  //
  void printPlayerInfo(int claimed_fields) const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Default constructor for the Player class. Initializes the id to A, the amount of chips to 0 and the has_passed
  /// variable to false. Explicit to avoid implicit conversions.
  //
  explicit Player(char id);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Default destructor for the Player class. The default destructor is used, because the Player class does not have
  /// any resources that need to be freed.
  //
  ~Player() = default;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Assignment operator for the Player class. The assignment operator is deleted, because the Player class does not
  /// have any resources that need to be freed.
  //
  Player &operator=(const Player &);
};

#endif //PLAYER_HPP