#include <vector>
#include <string>
#include "Command.hpp"

class Command {
private:
  CommandType type_;
  std::vector<std::string> parameters_;

  bool isQuit();
  CommandType getType();
  std::vector<std::string> &getParameters();
  void setType(CommandType type);
  void setParameters(std::vector<std::string> &parameters);

  Command(std::vector<std::string> &input);
  explicit Command(CommandType type);
  Command(Command& command);
  ~Command();
};

Command::Command(Command &command) {
  type_ = command.type_;
  parameters_ = command.parameters_;
}

Command::Command(CommandType type) {
  type_ = type;
}

Command::Command(std::vector<std::string> &input) {
  // TODO
}

Command::~Command() {
  // TODO: Change for the better
  type_ = CommandType::INVALID;
  parameters_ = std::vector<std::string>();
}

bool Command::isQuit() {
  return type_ == CommandType::QUIT;
}

CommandType Command::getType() {
  return type_;
}

std::vector<std::string> &Command::getParameters() {
  return parameters_;
}

void Command::setType(CommandType type) {
  type_ = type;
}

void Command::setParameters(std::vector<std::string> &parameters) {
  // remove the first word from the vector (Command type)
  parameters.erase(parameters.begin());
  parameters_ = parameters;
}

CommandType parseType(std::string &input) {
  if (input == "place") {
    return CommandType::PLACE;
  } else if (input == "pass") {
    return CommandType::PASS;
  } else {
    return CommandType::INVALID;
  }
}




