#include "Game.hpp"
#include "Utils.hpp"

Game::Game(int maximum_rounds, char *config_path) {
  // TODO
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
  // TODO
}
void Game::execute(Command command) {
  // TODO
}
bool Game::isRunning() {
  return phase_ != Phase::END;
}

