# Player

In this part of the description, you can find the details about the `Player` class which represents a player.
This class is responsible for storing information about the player such as their id and the amount of chips they have.

## `Player.hpp` / `Player.cpp`

### Class `Player`

#### Data Members (Member Variables)
- `id_`
    - stores the id of the player as `char`
- `chips_`
    - stores the number of unplaced chips the player has as `int`
- `has_passed_`
  - stores if the player has passed the current phase as `bool`

#### Constructor / Copy Constructor / Destructor

- `Player(char id)`
    - constructor of the class
    - initialises all data members accordingly
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- getter / setter / further methods as needed
