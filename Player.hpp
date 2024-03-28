#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
private:
  char id_;
  int chips_;
  bool has_passed_;
public:
  // Functions
  char getId();
  void setId(char id);
  int getChips();
  void setChips(int chips);
  bool getHasPassed();
  void setHasPassed(bool has_passed);
  // Constructor
  explicit Player(char id);
  ~Player() = default;
  Player& operator= (const Player&);
};

#endif //PLAYER_HPP