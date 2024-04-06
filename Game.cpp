#include <iostream>
#include "Game.hpp"
#include "Utils.hpp"

Game::Game(int maximum_rounds, char *config_path) {
  current_round_ = 1;
  max_rounds_ = maximum_rounds;
  phase_ = Phase::START;
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
  std::cout << "Welcome to OOPtimal Tactics!\nPlaying maximum of " << max_rounds_ << " round(s)!\n";
  announceRound();
  calculateChips();
  setPhase(Phase::PLACEMENT);
  printPlacePhase();
  printPlayerPrompt();
}

void Game::announceRound() const {
  std::cout << "\n";
  std::cout << "------------------\n";
  std::cout << "Round " << current_round_ << "/" << max_rounds_ << " starts!\n";
  std::cout << "------------------\n";
  std::cout << "\n";
}


void Game::printPlayerPrompt() {
  // TODO: Optimize
  if (phase_ == Phase::PLACEMENT) {
    if (current_round_ % 2 == 0) {
      active_player_ = player_b_;
    } else {
      active_player_ = player_a_;
    }
    std::cout << "Player " << active_player_->getId()
            << ", you have " << active_player_->getChips() << " chip(s) left, "
            "where and how do you want to place your chips?\n";
  } else {
    if (current_round_ % 2 == 0) {
      active_player_ = player_a_;
    } else {
      active_player_ = player_b_;
    }
    std::cout << "Player " << active_player_->getId() << ", what do you want to do?\n";
  }
}

void Game::execute(Command command) {
    if (command.isQuit()) {
      phase_ = Phase::END;
      endPhase();
    } else if (command.getType() == CommandType::INFO) {
      active_player_->printPlayerInfo(map_->getFieldsPerPlayer(*active_player_));
    } else if (command.getType() == CommandType::MAP) {
      map_->setIsOutputActive(!map_->getIsOutputActive());
    } else if (command.getType() == CommandType::PASS) {
      active_player_->setHasPassed(true);
    } else if (phase_ == Phase::PLACEMENT) {
      // TODO place command
    } else if (phase_ == Phase::MOVEMENT) {
      // TODO move command
    } else {
      std::cout << "!!!Command not recognized\n";
    }
}

void Game::printPlacePhase() {
  std::cout << "------------------\n";
  std::cout << "Placement Phase\n";
  std::cout << "------------------\n";
  map_->printMap();
  // Player can execute place command here
}

void Game::printMovePhase() {
  std::cout << "------------------\n";
  std::cout << "Movement Phase\n";
  std::cout << "------------------\n";
  map_->printMap();
}

void Game::endPhase() {
  std::cout << "------------------\n";
  std::cout << "GAME END!\n";
  std::cout << "\n";
  calculatePoints();
}

bool Game::isRunning() {
  return phase_ != Phase::END;
}

void Game::calculateChips() {
  // The number of chips gained is calculated by dividing
  // the number of fields currently claimed by the player by three and rounding up
  int player_a_chips = map_->getFieldsPerPlayer(*player_a_);
  int player_b_chips = map_->getFieldsPerPlayer(*player_b_);
  player_a_->setChips((player_a_chips / 3) + (player_a_chips % 3 != 0));
  player_b_->setChips((player_b_chips / 3) + (player_b_chips % 3 != 0));
}

void Game::calculatePoints() {
  // TODO Calculate points
}


Game::~Game() {
  delete player_a_;
  delete player_b_;
  delete map_;
}
