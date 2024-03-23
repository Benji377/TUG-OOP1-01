# Map

In this part of the description, you can find the details about the `Map` class which represents the map.
This class is responsible for storing information such as all the fields in the map and provides simple access to them.

## `Map.hpp` / `Map.cpp`

### Class `Map`

#### Data Members (Member Variables)

- `columns_`
  - stores the amount of columns the map has as `int`
- `rows_`
  - stores the amount of rows the map has as `int`
- `fields_`
    - stores the fields of the map as a 2d vector `std::vector<std::vector<Field*>>`
- `output_active_`
  - stores if the map output is active as `bool`

#### Constructor / Copy Constructor / Destructor

- `Map(char* config_path, Player* player_a, Player* player_b)`
    - constructor of the class
    - initialises all data members accordingly
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- getter / setter / further methods as needed
