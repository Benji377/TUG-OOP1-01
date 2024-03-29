#include <iostream>
#include "Game.hpp"
#include "Utils.hpp"

Game::Game(int maximum_rounds, char *config_path) {
  current_round_ = 0;
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

int Game::getRoundNumber(char *string) {
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
  std::cout << "\n";
  std::cout << "------------------\n";
  std::cout << "Round " << current_round_ << "/" << max_rounds_ << " starts!\n";
  std::cout << "------------------\n";
  std::cout << "\n";
  std::cout << "------------------\n";
  std::cout << "Placement Phase\n";
  std::cout << "------------------\n";
  map_->printMap();

}
void Game::execute(Command command) {
  if (command.isQuit()) {
    phase_ = Phase::END;
  } else if (command.getType() == CommandType::INFO) {
    // TODO print Player info
  } else if (command.getType() == CommandType::MAP) {
    map_->setIsOutputActive(!map_->getIsOutputActive());
  } else if (command.getType() == CommandType::PASS) {
    // TODO Player does nothing
  } else if (command.getType() == CommandType::PLACE) {
    // TODO:Place a chip
  } else if (command.getType() == CommandType::MOVE) {
    // TODO: Move a chip/player
  } else {
    // Command not implemented?
    std::cout << "Sorry not sorry";
  }
}

bool Game::isRunning() {
  return phase_ != Phase::END;
}

