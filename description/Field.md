# Field

In this part of the description, you can find the details about the `Field` class which represents a field on
the map. This class is responsible for storing information about who currently claims that field and with how many
chips.

## `Field.hpp` / `Field.cpp`

### Class `Field`

#### Data Members (Member Variables)

- `player_`
    - stores the player that currently claims this field as `Player*`
- `chips_`
    - stores the amount of chips on that field as `int`
- `is_water_`
    - stores information about the field type as `bool`

#### Constructor / Copy Constructor / Destructor

- `Field(Player* player, int chips, bool is_water)`
  - constructor of the class
  - initialises all data members accordingly
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- getter / setter / further methods as needed
