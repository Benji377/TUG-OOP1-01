//---------------------------------------------------------------------------------------------------------------------
//
// The Game class is the main class of the game. It contains the map, the players, the current round, the maximum rounds,
// the current phase and the active player. The class contains methods to get and set the map, the players, the current
// round, the maximum rounds, the current phase and the active player. The class also contains methods to announce the
// round, print the place phase, print the move phase, print the player prompt, end the phase, pass a command, place a
// command, move a command, calculate the chips, calculate the points, change the player, check the phase and go to the
// next round. The class also contains a constructor, copy constructor and destructor.
//
// Author: Benjamin Demetz
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "Player.hpp"
#include "Command.hpp"

enum class Phase {
  PLACEMENT,
  MOVEMENT,
  END
};

class Game {
private:
  Map *map_;
  Player *player_a_;
  Player *player_b_;
  int current_round_;
  int max_rounds_;
  Phase phase_;
  Player *active_player_;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Announces the current round by printing the round number
  //
  void announceRound() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Prints the place phase header and chooses the current active player
  //
  void printPlacePhase();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Prints the move phase header and chooses the current active player
  //
  void printMovePhase();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Prints the player prompt, asking the player what action to take
  //
  void printPlayerPrompt();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Ends the game and prints the winner
  //
  void endPhase();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Executes the pass command, by setting the player to pass this round/phase
  //
  void passCommand();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Executes the place command, by placing the player's chip on the map
  ///
  /// @param command The command to be executed, must be a place command
  //
  void placeCommand(Command command);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Executes the move command, by moving the player's chip on the map
  ///
  /// @param command The command to be executed, must be a move command
  //
  void moveCommand(Command command);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Calculates the amount of chips for each player by looking at the amount of fields they own
  //
  void calculateChips();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Calculates the points for each player by looking at the amount of fields they own
  //
  void calculatePoints();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Changes the active player to the other player or the same player if the condition is met
  //
  void changePlayer();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks the current phase and changes to the next one if needed
  //
  void checkPhase();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Goes to the next round by changing the current round and the phase
  //
  void nextRound();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Switches the active player at the start of the phases and resets its pass counter
  ///
  /// @param isPlacementPhase True if the phase is the placement phase, false otherwise
  //
  void switchPhasePlayer(bool isPlacementPhase);

public:
  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the map of the game
  ///
  /// @return The map of the game
  //
  Map *getMap();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the map of the game
  ///
  /// @param map The map to be set
  //
  void setMap(Map *map);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the first player of the game
  ///
  /// @return The first player of the game
  //
  Player *getPlayerA();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the first player of the game
  ///
  /// @param playerA The first player to be set
  //
  void setPlayerA(Player *playerA);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the second player of the game
  ///
  /// @return The second player of the game
  //
  Player *getPlayerB();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the second player of the game
  ///
  /// @param playerB The second player to be set
  //
  void setPlayerB(Player *playerB);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the current round of the game
  ///
  /// @return The current round of the game
  //
  int getCurrentRound() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the current round of the game
  ///
  /// @param currentRound The current round to be set
  //
  void setCurrentRound(int currentRound);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the maximum rounds of the game
  ///
  /// @return The maximum rounds of the game
  //
  [[nodiscard]] int getMaxRounds() const;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the maximum rounds of the game
  ///
  /// @param maxRounds The maximum rounds to be set
  //
  void setMaxRounds(int maxRounds);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the current phase of the game
  ///
  /// @return The current phase of the game
  //
  Phase getPhase();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the current phase of the game
  ///
  /// @param phase The current phase to be set
  //
  void setPhase(Phase phase);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the active player of the game
  ///
  /// @return The active player of the game
  //
  Player *getActivePlayer();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the active player of the game
  ///
  /// @param activePlayer The active player to be set
  //
  void setActivePlayer(Player *activePlayer);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the current round number converted from a string
  ///
  /// @param player_number The string to be converted
  ///
  /// @return The current round number
  //
  static int getRoundNumber(const char *string);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the round number is valid, meaning it is a positive number
  ///
  /// @param rounds The round number to be checked
  ///
  /// @return True if the round number is valid, false otherwise
  //
  static bool isValidRoundNumber(int rounds);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the config file is valid, meaning it exists and is not empty and the magic number is correct
  ///
  /// @param config_path The path to the config file
  ///
  /// @return True if the config file is valid, false otherwise
  //
  static bool isValidConfig(char *config_path);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Starts the game by setting the current round to 1 and the phase to placement
  //
  void start();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Executes a command by checking the phase and calling the appropriate method
  ///
  /// @param command The command to be executed
  //
  void execute(Command command);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the game is running, meaning the current round is less than or equal to the maximum rounds.
  /// It also makes sure that the current Phase is not the end phase.
  ///
  /// @return True if the game is running, false otherwise
  //
  bool isRunning();

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor of the Game class. It initializes the map, the players, the current round, the maximum rounds, the
  /// current phase and the active player.
  ///
  /// @param maximum_rounds The maximum rounds of the game
  /// @param config_path The path to the config file
  //
  Game(int maximum_rounds, char *config_path);

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy constructor of the Game class. It is deleted to prevent copying of the game.
  ///
  /// @param Game The Game to be copied
  //
  Game(const Game &) = delete;

  ///------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor of the Game class. It deletes the map, the players and the active player.
  //
  ~Game();
};

#endif //GAME_HPP
