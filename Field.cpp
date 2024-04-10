#include "Field.hpp"

Field::Field(Player *player, int chips, bool is_water) {
  player_ = player;
  chips_ = chips;
  is_water_ = is_water;
}

void Field::setPlayer(Player *player) {
  player_ = player;
}

Player *Field::getPlayer() {
  return player_;
}

void Field::setChips(int amount) {
  chips_ = amount;
}

int Field::getChips() const {
  return chips_;
}

void Field::setIsWater(bool is_water) {
  is_water_ = is_water;
}

bool Field::getIsWater() const {
  return is_water_;
}