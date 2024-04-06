#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
private:
  char id_;
  int chips_;
  bool has_passed_;
public:
  // Functions
  char getId() const;
  void setId(char id);
  int getChips() const;
  void setChips(int chips);
  bool getHasPassed() const;
  void setHasPassed(bool has_passed);
  // Constructor
  explicit Player(char id);
  ~Player() = default;
  Player& operator= (const Player&);
  void printPlayerInfo(int claimed_fields) const;
};

#endif //PLAYER_HPP