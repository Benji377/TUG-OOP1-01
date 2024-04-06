#ifndef FIELD_HP
#define FIELD_HP

#include "Player.hpp"

class Field {
private:
  Player *player_;
  int chips_;
  bool is_water_;
public:
  // Functions
  void setPlayer(Player *player);

  Player *getPlayer();

  void setChips(int amount);

  int getChips();

  void setIsWater(bool is_water);

  bool getIsWater();

  // Constructors
  Field(Player *player, int chips, bool is_water);

  Field(const Field &) = delete;

  Field &operator=(const Field &) = default;

  ~Field() = default;
};

#endif //FIELD_HP