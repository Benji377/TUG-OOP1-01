# Game

In this part of the description, you can find the details about the `Game` class which represents the whole game.
This class is responsible for storing information about the game such as storing the map, the players and everything
else needed by the game.

## `Game.hpp` / `Game.cpp`

### Enum (class) `Phase`

This enum (class) collects all possible phases the game could be in.
Those are `PLACEMENT`, `MOVEMENT`, `END`. You can add further options if needed.

> **Hint:** It is preferable to use strongly typed enum classes instead of ordinary enums.

### Class `Game`

#### Data Members (Member Variables)

- `map_`
    - stores the map as `Map*`
- `player_a_`
    - stores the first player as `Player*`
- `player_b_`
    - stores the second player as `Player*`
- `current_round_`
    - stores the current round as `ìnt`
- `max_rounds_`
    - stores the maximum number of rounds as `ìnt`
- `phase_`
    - stores the current game phase as `Phase`
- `active_player_`
  - stores the currently active player as `Player*` 

#### Constructor / Copy Constructor / Destructor

- `Game(int maximum_rounds, char* config_path)`
    - constructor of the class
    - initialises all data members accordingly
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- `static int getRoundNumber(char* string)`
  - Converts the passed round number string into an integer, returns -1 if conversion failed
- `static bool isValidRoundNumber(int rounds)`
  - Returns true if the passed int is a valid round number
- `static bool isValidConfig(char* config_path)`
  - Returns true if the config could be opened for reading and is valid
- `void start()`
  - Starts the game by printing the welcome message
- `void execute(Command command)`
  - executes a command inputted by the user
- `bool isRunning()`
  - Returns true if the game is running (not in the end phase)
- getter / setter / further methods as needed