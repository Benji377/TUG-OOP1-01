#include <string>
#include "Command.hpp"

//---------------------------------------------------------------------------------------------------------------------
///
/// A constructor that creates a Command object from an existing Command object
///
/// @param command The Command object to copy
///
//
Command::Command(Command &command) {
  type_ = command.getType();
  parameters_ = command.getParameters();
}

//---------------------------------------------------------------------------------------------------------------------
///
/// A constructor that creates a Command object from a CommandType
///
/// @param type The CommandType to set the Command object to
//
Command::Command(CommandType type) {
  type_ = type;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// A constructor that creates a Command object from a vector of strings
///
/// @param input The vector of strings to create the Command object from
//
Command::Command(std::vector<std::string> &input) {
  type_ = parseType(input.at(0));
  // Removes the first string containing the type of command
  input.erase(input.begin());
  parameters_ = input;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// A function that checks if the Command object is a quit command
///
/// @return True if the Command object is a quit command, false otherwise
//
bool Command::isQuit() {
  return type_ == CommandType::QUIT;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// A function that returns the type of the Command object
///
/// @return The type of the Command object
//
CommandType Command::getType() {
  return type_;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// A function that returns the parameters of the Command object
///
/// @return The parameters of the Command object
//
std::vector<std::string> &Command::getParameters() {
  return parameters_;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// A function that sets the type of the Command object
///
/// @param type The type to set the Command object to
//
void Command::setType(CommandType type) {
  type_ = type;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// A function that sets the parameters of the Command object
///
/// @param parameters The parameters to set the Command object to
//
void Command::setParameters(std::vector<std::string> &parameters) {
  // remove the first word from the vector (Command type)
  parameters.erase(parameters.begin());
  parameters_ = parameters;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// A function that parses a string to a CommandType
///
/// @param input The string to parse
///
/// @return The CommandType that the string represents or INVALID if the string is not a valid CommandType
//
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

//---------------------------------------------------------------------------------------------------------------------
///
/// An assignment operator that assigns a Command object to another Command object
///
/// @param command The Command object to assign
///
/// @return The Command object that was assigned
//
Command &Command::operator=(const Command&) {
  return *this;
}

