#include "Player.hpp"

Player::Player(char id) {
  id_ = id;
  chips_ = 0; // TODO
  has_passed_ = false; // TODO
}

char Player::getId() {
  return id_;
}
void Player::setId(char id) {
  id_ = id;
}

int Player::getChips() {
  return chips_;
}
void Player::setChips(int chips) {
  chips_ = chips;
}

bool Player::getHasPassed() {
  return has_passed_;
}
void Player::setHasPassed(bool has_passed) {
  has_passed_ = has_passed;
}

Player &Player::operator=(const Player &) {
  return *this;
}

