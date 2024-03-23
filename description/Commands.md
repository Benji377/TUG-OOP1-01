# Commands & Command Line Interface

In this part of the description, you can find the details about the classes `Command` and `CommandLine`.

## `Command.hpp` / `Command.cpp`

### Enum class `CommandType`

This enum class collects all possible command types that may be entered by a user.
Those are `PLACE`, `PASS`, `MOVE`, `MAP`, `INFO`, `QUIT`. It should also contain the types `INVALID` and `WRONG_PARAM`,
which are used to denote an invalid command and a command that was entered with the wrong number of parameters.

> **Hint:** You need to use a strongly typed enum class instead of an ordinary enum.

### Class `Command`

This class represents a command, consisting of a command type and parameters.

#### Data Members (Member Variables)

- `type_`
    - represents the command type that was entered by the user. Use the enum `CommandType` here.
- `parameters_`
    - stores all parameters that were entered by the user (not including the command type) as
      a `std::vector<std::string>`
    - e.g. for the command `place 2 1 4`, we would store `"2"`, `"1"` and `"4"` here.

#### Constructor / Copy Constructor / Destructor

- `Command(std::vector<std::string>& input)`
    - receives the user input (already split into words)
    - initialises the two data members accordingly
- `Command(CommandType type)`
    - additional constructor that receives the command type directly
    - only initialises `type_`
- Suitable copy constructors and destructors should be implemented. If the default ones are used, this should be done
  explicitly.

#### Methods

- `bool isQuit()`
    - returns `true`, if and only if the command type is `QUIT`
- `CommandType getType()`
    - getter for `type_`
- `std::vector<std::string>& getParameters()`
    - getter for `parameters_`
- `void setType(CommandType type)`
    - setter for `type_`
- further methods as needed

---

## `CommandLine.hpp` / `CommandLine.cpp`

### Class `CommandLine`

This class has already been provided to you. You can use the files as they are or extend them if needed.

#### Data Members (Member Variables)

- none

#### Constructor / Copy Constructor / Destructor

- `CommandLine()`
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- `Command readCommand()`
    - reads an input from the user and stores it in a `Command` object
- getter / setter / further methods as needed

