#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>

enum class CommandType {
  PLACE,
  PASS,
  MOVE,
  MAP,
  INFO,
  QUIT,
  INVALID,
  WRONG_PARAM
};

class Command {
private:
  CommandType type_;
  std::vector<std::string> parameters_;
  // Functions
  static CommandType parseType(std::string &input);
public:
  // Functions
  bool isQuit();
  CommandType getType();
  std::vector<std::string> &getParameters();
  void setType(CommandType type);
  void setParameters(std::vector<std::string> &parameters);
  // Constructors
  explicit Command(std::vector<std::string> &input);
  explicit Command(CommandType type);
  Command(Command& command);
  Command& operator= (const Command&);
  ~Command() = default;
};

#endif //COMMAND_HPP