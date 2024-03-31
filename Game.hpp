#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "Player.hpp"
#include "Command.hpp"

enum class Phase {
  START,
  PLACEMENT,
  MOVEMENT,
  END
};

class Game {
private:
  Map* map_;
  Player* player_a_;
  Player* player_b_;
  int current_round_;
  int max_rounds_;
  Phase phase_;
  Player* active_player_;
  void announceRound() const;
  void placePhase(Command command);
  void movePhase(Command command);
  void printPlayerPrompt();
  void endPhase();
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

  static int getRoundNumber(char* string);
  static bool isValidRoundNumber(int rounds);
  static bool isValidConfig(char* config_path);
  void start();
  void execute(Command command);
  bool isRunning();
  // Constructors
  Game(int maximum_rounds, char* config_path);
  Game(const Game&) = delete;
  ~Game() = default;
};

#endif //GAME_HPP
