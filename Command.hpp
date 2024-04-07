//----------------------------------------------------------------------------------------------------------------------
//
// The Command class is a simple class that stores the type of command and its parameters. It also contains a method to
// parse the type of command from a string. The class is used to store the user input in a structured way.
//
// Author: Benjamin Demetz
//---------------------------------------------------------------------------------------------------------------------
//

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

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A function that parses a string to a CommandType
  ///
  /// @param input The string to parse
  ///
  /// @return The CommandType that the string represents or INVALID if the string is not a valid CommandType
  //
  static CommandType parseType(std::string &input);

public:
  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A function that checks if the Command object is a quit command
  ///
  /// @return True if the Command object is a quit command, false otherwise
  //
  bool isQuit();

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A function that returns the type of the Command object
  ///
  /// @return The type of the Command object
  //
  CommandType getType();

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A function that returns the parameters of the Command object
  ///
  /// @return The parameters of the Command object
  //
  std::vector<std::string> &getParameters();

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A function that sets the type of the Command object
  ///
  /// @param type The type to set the Command object to
  //
  void setType(CommandType type);

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A function that sets the parameters of the Command object
  ///
  /// @param parameters The parameters to set the Command object to
  //
  void setParameters(std::vector<std::string> &parameters);

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A constructor that creates a Command object from a vector of strings
  ///
  /// @param input The vector of strings to create the Command object from
  //
  explicit Command(std::vector<std::string> &input);

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A constructor that creates a Command object from a CommandType
  ///
  /// @param type The CommandType to set the Command object to
  //
  explicit Command(CommandType type);

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A constructor that creates a Command object from an existing Command object
  ///
  /// @param command The Command object to copy
  ///
  //
  Command(Command &command);

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// An assignment operator that assigns a Command object to another Command object
  ///
  /// @param command The Command object to assign
  ///
  /// @return The Command object that was assigned
  //
  Command &operator=(const Command &);

  //-------------------------------------------------------------------------------------------------------------------
  ///
  /// A destructor for the Command object that is defaulted
  //
  ~Command() = default;
};

#endif //COMMAND_HPP