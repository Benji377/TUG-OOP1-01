#include <iostream>
#include "Game.hpp"
#include "Utils.hpp"

Game::Game(int maximum_rounds, char *config_path) {
  current_round_ = 1;
  max_rounds_ = maximum_rounds;
  phase_ = Phase::PLACEMENT;
  player_a_ = new Player('A');
  player_b_ = new Player('B');
  map_ = new Map(config_path, player_a_, player_b_);
  active_player_ = nullptr;
}

Map *Game::getMap() {
  return map_;
}

void Game::setMap(Map *map) {
  map_ = map;
}

Player *Game::getPlayerA() {
  return player_a_;
}

void Game::setPlayerA(Player *playerA) {
  player_a_ = playerA;
}

Player *Game::getPlayerB() {
  return player_b_;
}

void Game::setPlayerB(Player *playerB) {
  player_b_ = playerB;
}

int Game::getCurrentRound() const {
  return current_round_;
}

void Game::setCurrentRound(int currentRound) {
  current_round_ = currentRound;
}

int Game::getMaxRounds() const {
  return max_rounds_;
}

void Game::setMaxRounds(int maxRounds) {
  max_rounds_ = maxRounds;
}

Phase Game::getPhase() {
  return phase_;
}

void Game::setPhase(Phase phase) {
  phase_ = phase;
}

Player *Game::getActivePlayer() {
  return active_player_;
}

void Game::setActivePlayer(Player *activePlayer) {
  active_player_ = activePlayer;
}

int Game::getRoundNumber(const char *string) {
  int round_number = -1;
  Utils::decimalStringToInt(string, round_number);
  return round_number;
}

bool Game::isValidRoundNumber(int rounds) {
  return rounds >= 1;
}

bool Game::isValidConfig(char *config_path) {
  return Utils::isValidConfig(config_path);
}

void Game::start() {
  std::cout << "Welcome to OOPtimal Tactics!\nPlaying maximum of " << getMaxRounds() << " round(s)!\n";
  announceRound();
  calculateChips();
  printPlacePhase();
  printPlayerPrompt();
}

void Game::announceRound() const {
  std::cout << "\n";
  std::cout << "------------------\n";
  std::cout << "Round " << getCurrentRound() << "/" << getMaxRounds() << " starts!\n";
  std::cout << "------------------\n";
  std::cout << "\n";
}


void Game::printPlayerPrompt() {
  if (getPhase() == Phase::PLACEMENT) {
    std::cout << "Player " << getActivePlayer()->getId()
              << ", you have " << getActivePlayer()->getChips()
              << " chip(s) left, where and how do you want to place your chips?\n";
  } else {
    std::cout << "Player " << getActivePlayer()->getId() << ", what do you want to do?\n";
  }
}

void Game::printPlacePhase() {
  std::cout << "------------------\n";
  std::cout << "Placement Phase\n";
  std::cout << "------------------\n";
  switchPhasePlayer(true);
  getMap()->printMap();
}

void Game::printMovePhase() {
  std::cout << "------------------\n";
  std::cout << "Movement Phase\n";
  std::cout << "------------------\n";
  switchPhasePlayer(false);
  getMap()->printMap();
}

void Game::endPhase() {
  std::cout << "------------------\n";
  std::cout << "GAME END!\n";
  std::cout << "\n";
  calculatePoints();
}

void Game::passCommand() {
  getActivePlayer()->setHasPassed(true);
  // After a player uses the pass command, if possible the next player will be set as the active player
  changePlayer();
}

bool Game::isRunning() {
  if (getPhase() == Phase::END) {
    endPhase();
  }
  return getPhase() != Phase::END;
}

void Game::execute(Command command) {
  // Depending on the command type, the game will execute the command
  if (command.isQuit()) {
    setPhase(Phase::END);
    return;
  } else if (command.getType() == CommandType::INFO) {
    getActivePlayer()->printPlayerInfo(getMap()->getFieldsPerPlayer(getActivePlayer()));
  } else if (command.getType() == CommandType::MAP) {
    getMap()->setIsOutputActive(!getMap()->getIsOutputActive());
    getMap()->printMap(); // The function will print the map if the output is active and return otherwise
  } else if (command.getType() == CommandType::PASS) {
    passCommand();
  } else if (getPhase() == Phase::PLACEMENT) {
    placeCommand(command);
  } else if (getPhase() == Phase::MOVEMENT) {
    moveCommand(command);
  } else {
    std::cout << "[ERROR] Entered command not found!\n";
  }
  // Then we check the phase to see if the game should proceed to the next phase
  checkPhase();
}

void Game::checkPhase() {
  // If both players have no chips left, the game proceeds to the movement phase
  if (getPhase() == Phase::PLACEMENT && (
          (getPlayerA()->getChips() <= 0 && getPlayerB()->getChips() <= 0)
      || (getPlayerA()->getHasPassed() && getPlayerB()->getHasPassed())
      || (getPlayerA()->getHasPassed() && getPlayerB()->getChips() <= 0)
      || (getPlayerB()->getHasPassed() && getPlayerA()->getChips() <= 0))) {
    setPhase(Phase::MOVEMENT);
    printMovePhase();
  }
  // In the movement phase, to get to th next phase, both players must have passed
  if (getPhase() == Phase::MOVEMENT && getPlayerA()->getHasPassed() && getPlayerB()->getHasPassed()) {
    // After the movement phase, the game proceeds to the next round
    nextRound();
    setPhase(Phase::PLACEMENT);
  }
  // If there are no more fields left or if we are in the last round, the game ends
  if (getMap()->getFieldsPerPlayer(getPlayerA()) <= 0 || getMap()->getFieldsPerPlayer(getPlayerB()) <= 0 ||
      (getPlayerA()->getHasPassed() && getPlayerB()->getHasPassed()) || getPhase() == Phase::END) {
    setPhase(Phase::END);
  } else {
    // In all other instances, we print the player prompt and proceed with the game
    printPlayerPrompt();
  }
}

void Game::switchPhasePlayer(bool isPlacementPhase) {
  if (isPlacementPhase) {
    if (getCurrentRound() % 2 == 0) {
      setActivePlayer(getPlayerB());
    } else {
      setActivePlayer(getPlayerA());
    }
  } else {
    if (getCurrentRound() % 2 == 0) {
      setActivePlayer(getPlayerA());
    } else {
      setActivePlayer(getPlayerB());
    }
  }
  getPlayerA()->setHasPassed(false);
  getPlayerB()->setHasPassed(false);
}

void Game::nextRound() {
  // If the current round is less than the maximum rounds, we proceed to the next round
  if (getCurrentRound()+1 <= getMaxRounds()) {
    setCurrentRound(getCurrentRound() + 1);
    announceRound();
    calculateChips();
    printPlacePhase();
  } else {
    setPhase(Phase::END);
    return;
  }
}

void Game::placeCommand(Command command) {
  if (command.getType() == CommandType::PLACE) {
    // The command should have 3 parameters: amount, column, row
    int amount, field_column, field_row;
    bool amount_valid, field_column_valid, field_row_valid;
    // Try to convert the parameters to integers
    amount_valid = Utils::decimalStringToInt(command.getParameters()[0], amount);
    field_column_valid = Utils::decimalStringToInt(command.getParameters()[1], field_column);
    field_row_valid = Utils::decimalStringToInt(command.getParameters()[2], field_row);
    // Check if the parameters are valid
    if (amount_valid && field_column_valid && field_row_valid) {
      // Fixing the 1-based index to 0-based index
      field_column--;
      field_row--;
      if (amount > 0) {
        if (amount <= getActivePlayer()->getChips()) {
          // Finally place the chip on the field
          if (getMap()->placeChip(getActivePlayer(), amount, field_column, field_row)) {
            // Print the map and change the player
            getActivePlayer()->setChips(getActivePlayer()->getChips() - amount);
            getMap()->printMap();
            changePlayer();
          } else {
            std::cout << "[ERROR] Invalid field!\n";
          }
        } else {
          std::cout << "[ERROR] Invalid amount! Must be a number <= chips in player inventory!\n";
        }
      } else {
        std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
      }
    } else {
      if (amount_valid) {
        std::cout << "[ERROR] Invalid field!\n";
      } else {
        std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
      }
    }
  } else if (command.getType() == CommandType::MOVE) {
    std::cout << "[ERROR] Entered command is not valid in this phase!\n";
  }
}

void Game::moveCommand(Command command) {
  if (command.getType() == CommandType::MOVE) {
    // The command should have 5 parameters: amount, from_column, from_row, to_column, to_row
    int amount, from_field_column, from_field_row, to_field_column, to_field_row;
    bool amount_valid, from_field_column_valid, from_field_row_valid, to_field_column_valid, to_field_row_valid;
    // Try to convert the parameters to integers
    amount_valid = Utils::decimalStringToInt(command.getParameters()[0], amount);
    from_field_column_valid = Utils::decimalStringToInt(command.getParameters()[1], from_field_column);
    from_field_row_valid = Utils::decimalStringToInt(command.getParameters()[2], from_field_row);
    to_field_column_valid = Utils::decimalStringToInt(command.getParameters()[3], to_field_column);
    to_field_row_valid = Utils::decimalStringToInt(command.getParameters()[4], to_field_row);
    // Check if the parameters are valid
    if (amount_valid && from_field_column_valid && from_field_row_valid && to_field_column_valid && to_field_row_valid) {
      // Fixing the 1-based index to 0-based index
      from_field_column--;
      from_field_row--;
      to_field_column--;
      to_field_row--;
      // Finally move the chip from the origin to the destination
      if (getMap()->moveChip(getActivePlayer(), amount, from_field_column, from_field_row,
                             to_field_column, to_field_row)) {
        // Print the map and change the player
        getMap()->printMap();
        changePlayer();
      }
    } else {
      if (!amount_valid || amount < 1) {
        std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
      } else if (!from_field_column_valid || !from_field_row_valid) {
        std::cout << "[ERROR] Invalid origin!\n";
      } else {
        std::cout << "[ERROR] Invalid destination!\n";
      }
    }
  } else if (command.getType() == CommandType::PLACE){
    std::cout << "[ERROR] Entered command is not valid in this phase!\n";
  }
}

void Game::calculateChips() {
  // The number of chips gained is calculated by dividing
  // the number of fields currently claimed by the player by three and rounding up
  int player_a_chips = getMap()->getFieldsPerPlayer(getPlayerA());
  int player_b_chips = getMap()->getFieldsPerPlayer(getPlayerB());
  // The chips are then added to the player's inventory
  getPlayerA()->setChips(((player_a_chips / 3) + (player_a_chips % 3 != 0)) + getPlayerA()->getChips());
  getPlayerB()->setChips(((player_b_chips / 3) + (player_b_chips % 3 != 0)) + getPlayerB()->getChips());
}

void Game::calculatePoints() {
  int player_a_points = getMap()->getFieldsPerPlayer(getPlayerA());
  int player_b_points = getMap()->getFieldsPerPlayer(getPlayerB());
  std::cout << "Player " << getPlayerA()->getId() << " claimed " << player_a_points << " field(s)!\n";
  std::cout << "Player " << getPlayerB()->getId() << " claimed " << player_b_points << " field(s)!\n";
  if (player_a_points > player_b_points) {
    std::cout << "\n";
    std::cout << "Congratulations, Player " << getPlayerA()->getId() << "! You won!\n";
  } else if (player_a_points < player_b_points) {
    std::cout << "\n";
    std::cout << "Congratulations, Player " << getPlayerB()->getId() << "! You won!\n";
  }
}

void Game::changePlayer() {
  if (getPhase() == Phase::PLACEMENT) {
    if (getActivePlayer()->getId() == getPlayerA()->getId()) {
      if (getPlayerB()->getChips() != 0 && !getPlayerB()->getHasPassed()) {
        setActivePlayer(getPlayerB());
      }
    } else {
      if (getPlayerA()->getChips() != 0 && !getPlayerA()->getHasPassed()) {
        setActivePlayer(getPlayerA());
      }
    }
  } else {
    // If the active player has passed, the next player will be set as the active player
    if (getActivePlayer()->getId() == getPlayerA()->getId()) {
      // Furthermore, the player must have fields left to move chips from
      if (!getPlayerB()->getHasPassed() && getMap()->getFieldsPerPlayer(getPlayerB()) > 0){
        setActivePlayer(getPlayerB());
      }
    } else {
      if (!getPlayerA()->getHasPassed() && getMap()->getFieldsPerPlayer(getPlayerA()) > 0) {
        setActivePlayer(getPlayerA());
      }
    }
  }
}


Game::~Game() {
  delete player_a_;
  delete player_b_;
  delete map_;
}
