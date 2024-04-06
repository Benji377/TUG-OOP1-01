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
  void printPlayerInfo(int claimed_fields) const;

  // Constructor
  explicit Player(char id);
  ~Player() = default;
  Player &operator=(const Player &);
};

#endif //PLAYER_HPP