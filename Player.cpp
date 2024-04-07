#include <iostream>
#include "Player.hpp"

Player::Player(char id) {
  id_ = id;
  chips_ = 0;
  has_passed_ = false;
}

char Player::getId() const {
  return id_;
}

void Player::setId(char id) {
  id_ = id;
}

int Player::getChips() const {
  return chips_;
}

void Player::setChips(int chips) {
  if (chips < 0) {
    chips = 0;
  }
  chips_ = chips;
}

bool Player::getHasPassed() const {
  return has_passed_;
}

void Player::setHasPassed(bool has_passed) {
  has_passed_ = has_passed;
}

void Player::printPlayerInfo(int claimed_fields) const {
  std::cout << "Player " << getId() << ":\n";
  std::cout << "You have " << getChips() << " chip(s) saved!\n";
  std::cout << "You own " << claimed_fields << " field(s)!\n";
  std::cout << "\n";
}

Player &Player::operator=(const Player &) {
  return *this;
}

