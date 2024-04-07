#include <iostream>
#include "Game.hpp"
#include "Utils.hpp"

// TODO
// - The chips must be carried from round to round and not resetted, as it is now
// - Error messages are missing
// - Clean up the code

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

int Game::getCurrentRound() {
  return current_round_;
}

void Game::setCurrentRound(int currentRound) {
  current_round_ = currentRound;
}

int Game::getMaxRounds() {
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
  if (getCurrentRound() % 2 == 0) {
    setActivePlayer(getPlayerB());
  } else {
    setActivePlayer(getPlayerA());
  }
  printPlayerPrompt();
}

void Game::announceRound() {
  std::cout << "\n";
  std::cout << "------------------\n";
  std::cout << "Round " << getCurrentRound() << "/" << getMaxRounds() << " starts!\n";
  std::cout << "------------------\n";
  std::cout << "\n";
}


void Game::printPlayerPrompt() {
  if (getPhase() == Phase::PLACEMENT) {
    std::cout << "Player " << getActivePlayer()->getId()
              << ", you have " << getActivePlayer()->getChips() << " chip(s) left, "
                                                                   "where and how do you want to place your chips?\n";
  } else {
    std::cout << "Player " << getActivePlayer()->getId() << ", what do you want to do?\n";
  }
}

void Game::execute(Command command) {
  if (command.isQuit()) {
    setPhase(Phase::END);
  } else if (command.getType() == CommandType::INFO) {
    getActivePlayer()->printPlayerInfo(getMap()->getFieldsPerPlayer(*getActivePlayer()));
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

  if (getPlayerA()->getChips() == 0 && getPlayerB()->getChips() == 0 && getPhase() == Phase::PLACEMENT) {
    setPhase(Phase::MOVEMENT);
    printMovePhase();
    if (getCurrentRound() % 2 == 0) {
      setActivePlayer(getPlayerA());
    } else {
      setActivePlayer(getPlayerB());
    }
  }
  if ((getPlayerA()->getHasPassed() && getPlayerB()->getHasPassed()) || getPhase() == Phase::END) {
    setPhase(Phase::END);
  } else {
    printPlayerPrompt();
  }
}

void Game::printPlacePhase() {
  std::cout << "------------------\n";
  std::cout << "Placement Phase\n";
  std::cout << "------------------\n";
  getMap()->printMap();
}

void Game::printMovePhase() {
  std::cout << "------------------\n";
  std::cout << "Movement Phase\n";
  std::cout << "------------------\n";
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
  if (getActivePlayer()->getId() == getPlayerA()->getId()) {
    setActivePlayer(getPlayerB());
  } else {
    setActivePlayer(getPlayerA());
  }

  if ((getPlayerA()->getChips() == 0 && getPlayerB()->getHasPassed()) ||
  (getPlayerB()->getChips() == 0 && getPlayerA()->getHasPassed())) {
    if (getPhase() == Phase::PLACEMENT) {
      setPhase(Phase::MOVEMENT);
      if (getCurrentRound() % 2 == 0) {
        setActivePlayer(getPlayerA());
      } else {
        setActivePlayer(getPlayerB());
      }
      printMovePhase();
    }
  }

  if (getPlayerA()->getHasPassed() && getPlayerB()->getHasPassed()) {
    if (getPhase() == Phase::PLACEMENT) {
      setPhase(Phase::MOVEMENT);
      if (getCurrentRound() % 2 == 0) {
        setActivePlayer(getPlayerA());
      } else {
        setActivePlayer(getPlayerB());
      }
      printMovePhase();
    } else {
      if (getCurrentRound()+1 <= getMaxRounds()) {
        setCurrentRound(getCurrentRound() + 1);
        announceRound();
        calculateChips();
        setPhase(Phase::PLACEMENT);
        printPlacePhase();
      } else {
        setPhase(Phase::END);
        endPhase();
        return;
      }
    }
    // Reset the hasPassed flag
    getPlayerA()->setHasPassed(false);
    getPlayerB()->setHasPassed(false);
  }
}

void Game::placeCommand(Command command) {
  if (command.getType() == CommandType::PLACE) {
    if (command.getParameters().size() == 3) {
      int amount, field_column, field_row;
      if (Utils::decimalStringToInt(command.getParameters()[0], amount) &&
          Utils::decimalStringToInt(command.getParameters()[1], field_column) &&
          Utils::decimalStringToInt(command.getParameters()[2], field_row)) {
        // Fixing the 1-based index to 0-based index
        field_column--;
        field_row--;
        if (amount > 0) {
          if (amount <= getActivePlayer()->getChips()) {
            if (getMap()->placeChip(*getActivePlayer(), amount, field_column, field_row)) {
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
        if (Utils::decimalStringToInt(command.getParameters()[0], amount)) {
          std::cout << "[ERROR] Invalid field!\n";
        } else {
          std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
        }
      }
    }
  } else if (command.getType() == CommandType::MOVE) {
    std::cout << "[ERROR] Entered command is not valid in this phase!\n";
  }
}

void Game::moveCommand(Command command) {
  if (command.getType() == CommandType::MOVE) {
    if (command.getParameters().size() == 5) {
      int amount, from_field_column, from_field_row, to_field_column, to_field_row;
      bool amount_valid, from_field_column_valid, from_field_row_valid, to_field_column_valid, to_field_row_valid;
      amount_valid = Utils::decimalStringToInt(command.getParameters()[0], amount);
      from_field_column_valid = Utils::decimalStringToInt(command.getParameters()[1], from_field_column);
      from_field_row_valid = Utils::decimalStringToInt(command.getParameters()[2], from_field_row);
      to_field_column_valid = Utils::decimalStringToInt(command.getParameters()[3], to_field_column);
      to_field_row_valid = Utils::decimalStringToInt(command.getParameters()[4], to_field_row);
      if (amount_valid && from_field_column_valid && from_field_row_valid && to_field_column_valid && to_field_row_valid) {
        // Fixing the 1-based index to 0-based index
        from_field_column--;
        from_field_row--;
        to_field_column--;
        to_field_row--;
        if (getMap()->moveChip(*getActivePlayer(), amount, from_field_column, from_field_row,
                               to_field_column, to_field_row)) {
          getMap()->printMap();
          changePlayer();
          if (getMap()->getFieldsPerPlayer(*getPlayerA()) == 0 || getMap()->getFieldsPerPlayer(*getPlayerB()) == 0) {
            setPhase(Phase::END);
            endPhase();
          }
        }
      } else {
        if (!amount_valid || amount <= 0) {
          std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
        } else if (!from_field_column_valid || !from_field_row_valid) {
          std::cout << "[ERROR] Invalid origin!\n";
        } else {
          std::cout << "[ERROR] Invalid destination!\n";
        }
      }
    }
  } else if (command.getType() == CommandType::PLACE){
    std::cout << "[ERROR] Entered command is not valid in this phase!\n";
  }
}

bool Game::isRunning() {
  if (getMap()->getFieldsPerPlayer(*getPlayerA()) == 0 && getMap()->getFieldsPerPlayer(*getPlayerB()) == 0) {
    setPhase(Phase::END);
    endPhase();
  }

  if (getCurrentRound() > getMaxRounds()) {
    setPhase(Phase::END);
    endPhase();
  }
  return getPhase() != Phase::END;
}

void Game::calculateChips() {
  // The number of chips gained is calculated by dividing
  // the number of fields currently claimed by the player by three and rounding up
  int player_a_chips = getMap()->getFieldsPerPlayer(*getPlayerA());
  int player_b_chips = getMap()->getFieldsPerPlayer(*getPlayerB());
  //std::cout << "Player " << getPlayerA()->getId() << " has " << getPlayerA()->getChips() << " chip(s)!\n";
  //std::cout << "Player " << getPlayerB()->getId() << " has " << getPlayerB()->getChips() << " chip(s)!\n";
  //std::cout << "Player " << getPlayerA()->getId() << " gained " << ((player_a_chips / 3) + (player_a_chips % 3 != 0)) << " chip(s)!\n";
  //std::cout << "Player " << getPlayerB()->getId() << " gained " << ((player_b_chips / 3) + (player_b_chips % 3 != 0)) << " chip(s)!\n";

  getPlayerA()->setChips(((player_a_chips / 3) + (player_a_chips % 3 != 0)) + getPlayerA()->getChips());
  getPlayerB()->setChips(((player_b_chips / 3) + (player_b_chips % 3 != 0)) + getPlayerB()->getChips());
}

void Game::calculatePoints() {
  std::cout << "Player " << getPlayerA()->getId() << " claimed " << getMap()->getFieldsPerPlayer(*getPlayerA())
            << " field(s)!\n";
  std::cout << "Player " << getPlayerB()->getId() << " claimed " << getMap()->getFieldsPerPlayer(*getPlayerB())
            << " field(s)!\n";
  if (getMap()->getFieldsPerPlayer(*getPlayerA()) > getMap()->getFieldsPerPlayer(*getPlayerB())) {
    std::cout << "\n";
    std::cout << "Congratulations, Player " << getPlayerA()->getId() << "! You won!\n";
  } else if (getMap()->getFieldsPerPlayer(*getPlayerA()) < getMap()->getFieldsPerPlayer(*getPlayerB())) {
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
    if (getActivePlayer()->getId() == getPlayerA()->getId()) {
      if (!getPlayerB()->getHasPassed()) {
        setActivePlayer(getPlayerB());
      }
    } else {
      if (!getPlayerA()->getHasPassed()) {
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
