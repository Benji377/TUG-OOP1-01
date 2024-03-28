#include <string>
#include "Command.hpp"

Command::Command(Command &command) {
  type_ = command.type_;
  parameters_ = command.parameters_;
}

Command::Command(CommandType type) {
  type_ = type;
}

Command::Command(std::vector<std::string> &input) {
  type_ = parseType(input.at(0));
  input.erase(input.begin());
  parameters_ = input;
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

CommandType Command::parseType(std::string &input) {
  if (input == "place") {
    return CommandType::PLACE;
  } else if (input == "pass") {
    return CommandType::PASS;
  } else if (input == "move") {
    return CommandType::MOVE;
  } else if (input == "map") {
    return CommandType::MAP;
  } else if (input == "info") {
    return CommandType::INFO;
  } else if (input == "quit") {
    return CommandType::QUIT;
  } else {
    return CommandType::INVALID;
  }
}

Command &Command::operator=(const Command&) {
  return *this;
}

