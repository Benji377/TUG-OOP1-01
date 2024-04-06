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

  void announceRound();
  void printPlacePhase();
  void printMovePhase();
  void printPlayerPrompt();
  void endPhase();
  void passCommand();
  void placeCommand(Command command);
  void moveCommand(Command command);
  void calculateChips();
  void calculatePoints();
  void changePlayer();

public:
  // Functions
  Map *getMap();
  void setMap(Map *map);
  Player *getPlayerA();
  void setPlayerA(Player *playerA);
  Player *getPlayerB();
  void setPlayerB(Player *playerB);
  int getCurrentRound();
  void setCurrentRound(int currentRound);
  int getMaxRounds();
  void setMaxRounds(int maxRounds);
  Phase getPhase();
  void setPhase(Phase phase);
  Player *getActivePlayer();
  void setActivePlayer(Player *activePlayer);
  static int getRoundNumber(const char *string);
  static bool isValidRoundNumber(int rounds);
  static bool isValidConfig(char *config_path);
  void start();
  void execute(Command command);
  bool isRunning();

  // Constructors
  Game(int maximum_rounds, char *config_path);
  Game(const Game &) = delete;
  ~Game();

};

#endif //GAME_HPP
