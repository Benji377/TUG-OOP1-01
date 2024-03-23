# Assignment 1 - OOPtimal Tactics

## Introduction

In Assignment 1 (A1) of the OOP1 practicals (KU) you will implement a simple tactical round-based game where two players
compete in claiming the most amount of tiles on a grid-based map.

This document describes the structure of the assignment and the expected functionality of the program.

## Learning Goals

- Foundations of classes:
    - attributes, methods
    - constructor, copy constructor, destructor
- Strings & streams:
    - `std::string`
    - files
- Some data structures of the standard library:
    - e.g. `std::vector`

## Specification

Some general specifications must be followed for every assignment in this course. A list of these specifications can be
found
here: [Assessment of Assignments - Deductions](https://www.notion.so/coding-tugraz/Assessment-of-Assignments-How-do-you-get-your-points-work-in-progress-00d2624846f4491391b389e6a48fa180?pvs=4#0af0c923deff4c4bb8740f5698aca451)

Please follow these specifications to avoid point deductions.

Additionally, the following specifications must be followed for this assignment (A1) as well:

- You **must** implement and use all described classes in your assignment. The required classes are described in detail in
  the [description folder](./description). 
- The provided `main.cpp` **must not** be changed and is replaced with the original version in our test system. The existing functionalities in `Utils.hpp/cpp` and `CommandLine.hpp/cpp` should not be changed, however, you are allowed to extend these classes.
- In this assignment (but only in this one), you do not have to check if memory was allocated successfully.
- Your implementation needs to follow the so-called "Rule of 3". That means that for every class, the constructor, 
copy constructor and destructor needs to be implemented, explicitly set to default, or deleted.

If any of these specifications are not followed, this may result in a deduction of up to -25 % per specification.

## Grading

Assignment 1 is worth **16 points**.

**Attention:** To receive a positive grade on the OOP1 KU **at least half of the public test cases for A1 have to be
passed**
(among other conditions).

Information on how your assignment submission will be assessed can be found
here: [Assessment of Assignments](https://www.notion.so/coding-tugraz/Assessment-of-Assignments-How-do-you-get-your-points-work-in-progress-00d2624846f4491391b389e6a48fa180)

Here you can find an overview of how your total grade for the KU will be
calculated: [Procedure and Grading](https://www.notion.so/coding-tugraz/Practicals-structure-grading-and-plagiarism-work-in-progress-76127221ed43451abc7ffba7852595e3)

There will not be any assignment interviews for A1.

## Submission

- Push to your repository
- The last commit on the main branch before the deadline will be graded
- Deliverables: all .cpp and .hpp files needed to run your program
- **Deadline: 10.04.2024, 23:59 (GMT+1)**
- **Assignment 1 is solo work!** See
  our [Guidelines on Plagiarism](https://www.notion.so/coding-tugraz/Practicals-structure-grading-and-plagiarism-work-in-progress-76127221ed43451abc7ffba7852595e3?pvs=4#93a62cfe219949929fa2fc41f2f1ff37)

## General Notes

The notes given in this section are important for the whole assignment description.

> **Note:** Any changes made to the upstream repository will be announced on our Discord server. Please make sure to
> [join the server](https://discord.gg/73EeHV6eDn) and then join the OOP1 group in the #role channel.

- `\n` shouldn't be printed as separate characters, instead it represents the newline character.
- Note the leading and trailing whitespaces in the text fields! You can make them visible by selecting the text field.
- Words in sharp brackets (like `<PLAYER_ID>`) should be replaced by calculated or given data. They are *not* part of
  the output itself! For a better understanding you can look at the example output at the end of this document.
- The user input is **case-insensitive**. This means that `move`, `MoVe` and `MOVE` would all be valid inputs.
- All additional whitespaces (leading, trailing, or additional whitespaces between command and parameters or between two
  parameters) in the input should be ignored.
- The program needs to be able to handle arbitrary input in any form (e.g. strings when integers are expected).

## Framework

We provide to you a `main.cpp` which must be used as the starting point of your program. This file must not be changed, as it will be replaced by the test system with the original version, so your program must be compatible with it.

Additionally, we provide the class Utils (`Utils.hpp/Utils.cpp`), which contains a function to safely convert a string to an integer,
and the class CommandLine (`CommandLine.hpp/cpp`), which should be used to convert user input into Command objects. 
The existing functionality should not be changed, but you can extend those classes if needed.

## Custom Data Types

After reading the Assignment Description below, it is recommended to start with the definition of the custom data types
used in this program. Descriptions for all of
these data types can be found in the [description folder](./description). In this first step, it is not required to actually implement
any of the described methods in detail, but they should be declared at least. Keep in mind that all data members (member
variables) of all classes should be declared as `private`. You are allowed to add further member variables and methods to all classes.

## Assignment Description

In this assignment you will implement a simple tactical round-based game where two players compete in claiming the
most fields on a grid-based map. The two competing players will be called `Player A` and `Player B`.

Each round the players will get some chips that they can strategically place in the `Placement Phase` of the round on 
owned fields to protect them. In the following `Movement Phase` of the round they can move chips 
 to claim empty fields or fields that the other player currently owns. Each field can hold multiple chips, but only from one player at a time.

The game ends when one player does not own any more fields or the specified maximum round number has been reached.

<details>
<summary><h3>Starting the Game</h3></summary>

The program is called with two command line parameters. The first parameter is the maximum number of rounds to be played
and the second parameter is the path to a config file that contains the layout of the map and the starting positions of
each player.

For example:

```
./a1 10 configs/config_01.txt
```

If the program is called

- with the wrong number of parameters
- with an invalid maximum round number (valid is only an integer greater or equal to 1)
- with a config file that cannot be opened
- with a config file that does not start with the
  correct [magic number](https://en.wikipedia.org/wiki/Magic_number_(programming)) (`OOP\n`)

the corresponding error message should be printed and the program should terminate with the correct return
value (see [Return Values and Error Messages](#return-values-and-error-messages)).

<details>
<summary><h4>Parsing the Config File</h4></summary>

The config file should then be parsed.

Every config file contains a [magic number](https://de.wikipedia.org/wiki/Magische_Zahl_(Informatik)) in the first line
(`OOP\n`). This string has to be checked for its correctness. If the magic number is correct you can assume that the
file is correctly formatted and no further checks of the file's content are needed.

In the second line, the dimension of the game map is represented in the format `<WIDTH>_<HEIGHT>`. Example: `4_5`

After that, the map data itself will span over the remaining lines. Each line represents a single row of the map, with:

- the character `a` being a start field of `Player A`
- the character `b` being a start field of `Player B`
- the character `0` being an empty field
- the character `-` being a water field

A valid config file could for example look like this:

```txt
OOP\n
4_5\n
aaa0\n
0000\n
00--\n
00--\n
0bbb\n
```

A start field means the player currently claims this field and has one `chip` on it at the start.

</details>

<details>

<summary><h4>Welcome Message</h4></summary>

After parsing the config file, the game should start by greeting the players with the output:

```
Welcome to OOPtimal Tactics!
Playing maximum of <ROUNDS> round(s)!
```

`<ROUNDS>` should be replaced by the supplied command line parameter for the maximum rounds.
After that the first round starts.

</details>
</details>

<details>
<summary><h3>Map Output</h3></summary>

During the game, the current map status that has resulted from parsing the config file and the players' moves will be
printed multiple times.
The map should always be printed in the following format:

- A singular claimed field will always be printed in the format: `<PLAYER_ID> <CHIPS_ON_FIELD>`. For simplicity, you do not 
need to handle the case that the amount of chips on a field exceeds 9, so the number will always be a single digit.
- If the field is empty (no player currently claims that field) it should be printed as three spaces
<code>&nbsp;&nbsp;&nbsp;</code>. 
- If the field is a water field it should be printed as <code>&nbsp;~&nbsp;</code>.

Example field claimed by `Player A` with 2 chips on it:

```
A 2
```

Example water field (pay attention to the spaces):

```
 ~ 
```

The map should be printed by combining all fields and using `|` as a separator between horizontally connected fields.
The axes should be indexed by numbers starting with 1. For simplicity, you do not need to handle the case where the height or the width of the map exceeds 9, so the index will always be a single digit.
The map is always followed by an empty line.
If the map output was deactivated (see Playing the Game > General Commands > Command map) the empty line should also not be printed.

Using the example config from above, at the beginning of the game the map would look like this:

```
  | 1 | 2 | 3 | 4 \n
1 |A 1|A 1|A 1|   \n
2 |   |   |   |   \n
3 |   |   | ~ | ~ \n
4 |   |   | ~ | ~ \n
5 |   |B 1|B 1|B 1\n
\n
```
</details>


<details>
<summary><h3>Round Overview</h3></summary>

At the start of each round the following message should be printed:

```
\n
------------------\n
Round <CURRENT_ROUND>/<MAX_ROUNDS> starts!\n
------------------\n
\n
```

where

- `<CURRENT_ROUND>` should be replaced by the current round
- `<MAX_ROUNDS>` should be replaced by the maximum number of rounds to be played

Then both players receive chips that they can place down in the `Placement Phase`.
The number of chips gained is calculated by dividing the number of fields currently claimed by the player by three and rounding up.

$`\textrm{<CHIPS\_GAINED> = }\left \lceil{\frac{\textrm{<NUMBER\_OF\_FIELDS\_CLAIMED\_BY\_THAT\_PLAYER>}}{3.0}}\right \rceil`$

Next follows the `Placement Phase`, where the players can place the chips they just received and any previously
unplaced chips on the map.

After that, in the `Movement Phase`, the players can move their chips on the map between adjacent fields and/or try to
claim additional fields for themselves.

The `Placement Phase` and the `Movement Phase` are described in more detail below.

</details>


<details>
<summary><h3>Playing the Game</h3></summary>

The players control the game by typing commands in the command line interface. Depending on if the game is currently in the 
`Placement Phase` or the `Movement Phase`, a different question is asked to prompt the player for input. The question is followed
by the command prompt <code>&nbsp;>&nbsp;</code> (Note the leading and trailing space!).

Unknown commands or commands that are not valid in the current phase should cause an error. All commands should be checked for the errors
specified in their description. If there is an error while parsing a command, print the correct error message
(see [Return Values and Error Messages](#return-values-and-error-messages)) and proceed by prompting the player for
input again with the question and the command prompt.

<details>
<summary><h4>General Commands</h4></summary>

The following commands should work in both the `Placement Phase` and the `Movement Phase` of the game.

<details>
<summary><h5>Command quit</h5></summary>

Syntax: `quit`

This command stops the game. The program should release all its resources
and terminate with the return value `0`.

**Error Handling**  
The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):
- The command was called with too many or too few parameters

</details>


<details>
<summary><h5>Command info</h5></summary>

Syntax: `info`

This command shows some information about the current player:

```
Player <PLAYER_ID>:\n
You have <CHIPS> chip(s) saved!\n
You own <NUMBER_OF_CLAIMED_FIELDS> field(s)!\n
\n
```

where

- `<PLAYER_ID>` should be replaced by the player id (the capital letter `A` or `B`)
- `<CHIPS>` should be replaced by the amount of available chips left for that player
- `<NUMBER_OF_CLAIMED_FIELDS>` should be replaced by the number of fields claimed by that player

This command does not end the player's turn.

**Error Handling**  
The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):
- The command was called with too many or too few parameters

</details>


<details>
<summary><h5>Command map</h5></summary>

Syntax: `map`

This command activates or deactivates the output of the map.

Initially the output of the map is active.
If the output of the map is active and the command `map` is entered, the output is deactivated.
For all further turns, the map is not printed anymore.
If the output of the map is not active and the command `map` is entered, the output is activated.
The map is printed once immediately. The output of the map then stays active for the following turns.

This command does not end the player's turn.

**Error Handling**  
The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):
- The command was called with too many or too few parameters

</details>


<details>
<summary><h5>Command pass</h5></summary>

Syntax: `pass`

If a player does not want to play any more commands in the current phase they can use the `pass` command.
**The player will then not be prompted for any further commands in this phase.** The other player will continue playing 
in the current phase. If both players have passed in a phase, 
the phase ends.

**Error Handling**  
The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):
- The command was called with too many or too few parameters

</details>
</details>

<details>
<summary><h4>Placement Phase</h4></summary>

In this phase the players can place their received chips and any chips they have leftover from previous rounds. This phase continues until both players are finished with this
phase, either by having no chips left or by using a `pass` command. Afterwards the `Movement Phase` starts.

Unplaced chips will be carried over to the next round.

First print the following header:

```
------------------\n
Placement Phase\n
------------------\n
<MAP>
```

where

- `<MAP>` should be replaced by the current status of the map (see Map Output). If the map output is
  deactivated, the header should be printed without the map.

Then the players take turns placing their chips on fields previously claimed by themselves, starting in odd rounds
with `Player A` and in even
rounds with `Player B`.

The following prompt should be printed every time a player is asked to input a command in this phase:

```
Player <PLAYER_ID>, you have <CHIPS> chip(s) left, where and how do you want to place your chips?\n
 > 
```

where

- `<PLAYER_ID>` should be replaced by the player id
- `<CHIPS>` should be replaced by the amount of unplaced chips left for that player.

The players can use one additional command in the `Placement Phase`:

<details>
<summary><h5>Command place</h5></summary>

The players can place their chips on claimed fields (meaning fields that already have some of their own chips on them)
with the `place` command.

Syntax: `place <AMOUNT> <FIELD_COLUMN> <FIELD_ROW>`

where

- `<AMOUNT>` is the amount of chips the player wants to place
- `<FIELD_COLUMN>` is the column coordinate of the field where the player wants to place the chips
- `<FIELD_ROW>` is the row coordinate of the field where the player wants to place the chips

If the command was successful the amount of chips specified should be added to the selected field, the
current player's turn ends and the map should be printed. If the map output is deactivated, nothing should be printed.
Then the other player's turn starts, or the `Placement Phase` ends if both players are finished in this phase.

**Error Handling**  
The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):
- The command was called with too many or too few parameters
- The command cannot be used in this phase
- The supplied amount is invalid. Must be an integer and > 0
- The supplied amount is invalid. Must be an integer and <= amount of available chips
- The supplied field is invalid, out of range or not claimed by the executing player

</details>
</details>

<details>
<summary><h4>Movement Phase</h4></summary>

In this phase the players can move their chips between adjacent fields and/or try to claim additional fields for
themselves. This phase continues until both players have passed. Afterwards the next round starts or the game ends if
no more rounds are left.

First print the following header:

```
------------------\n
Movement Phase\n
------------------\n
<MAP>
```

where

- `<MAP>` should be replaced by the current status of the map (see Map Output). If the map output is
  deactivated, the header should be printed without the map.

Then the players take turns, starting in odd rounds with `Player B` and in even rounds with `Player A`.
This is the exact opposite as in the `Placement Phase`!

The following prompt should be printed every time a player is asked to input a command in this phase:

```
Player <PLAYER_ID>, what do you want to do?\n
 > 
```

where

- `<PLAYER_ID>` should be replaced by the player id

The players can use one extra command in the `Movement Phase`:

<details>
<summary><h5>Command move</h5></summary>

With the command `move` the players can move a specific amount of chips from one field to another one.

Syntax: `move <AMOUNT> <FROM_FIELD_COLUMN> <FROM_FIELD_ROW> <TO_FIELD_COLUMN> <TO_FIELD_ROW>`

where

- `<AMOUNT>` is the amount of chips the player wants to move (valid numbers can be between inclusive 1 and inclusive the number of chips on the origin field)
- `<FROM_FIELD_COLUMN>` is the column coordinate of the origin field
- `<FROM_FIELD_ROW>` is the row coordinate of the origin field
- `<TO_FIELD_COLUMN>` is the column coordinate of the destination field
- `<TO_FIELD_ROW>` is the row coordinate of the destination field

Chips can only move to directly adjacent fields (including diagonals), so the up to 8 fields around the origin field.
There is no movement allowed outside the map borders.

If the destination field is unclaimed, the executing player will claim the destination field and the selected
amount of chips will be removed from the origin field and added to the destination field.

If the destination field is claimed by the executing player, the selected amount of chips will be
removed from the origin field and added to the destination field.

If the destination field is claimed by the other player, the following formula should be used to calculate the new
amount of chips on that field: 

`<NEW_DESTINATION_FIELD_AMOUNT> = <DESTINATION_FIELD_AMOUNT> + 1 - <CHIPS_TO_BE_MOVED>`  

- If the `<NEW_DESTINATION_FIELD_AMOUNT>` is zero the field will become unclaimed.   
- If the `<NEW_DESTINATION_FIELD_AMOUNT>` is a negative number the field will be claimed by the executing player and
the chip amount on that field should be `<NEW_DESTINATION_FIELD_AMOUNT> * (-1)`.
- If the `<NEW_DESTINATION_FIELD_AMOUNT>` is a positive number the field stays claimed by the other player and the chip
amount on that field should be `<NEW_DESTINATION_FIELD_AMOUNT>`.

If the command was successful the turn for the current player ends and the map should be printed. If the map output is
deactivated, nothing should be printed.
If either player now has zero claimed fields the game should go into the end phase (see End Phase).
Otherwise the next round starts.

**Error Handling**  
The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):
- The command was called with too many or too few parameters
- The command cannot be used in this phase
- The supplied amount is invalid. Must be an integer and > 0
- The supplied origin field is invalid, out of bounds or not claimed by the executing player
- The supplied amount is invalid. Must be an integer and <= chips on origin field
- The supplied destination field is invalid, out of bounds, out of range or is a water field

</details>
</details>
</details>


<details>
<summary><h3>End Phase</h3></summary>

The game ends if no more rounds are left at the end of a `Movement Phase`, or immediately if a player does not have any
claimed fields left.

First print the following header:

```
------------------\n
GAME END!\n
\n
```

After that the following information message should be printed first for `Player A` and then for `Player B`:

```
Player <PLAYER_ID> claimed <NUMBER_OF_CLAIMED_FIELDS> field(s)!\n
```

where

- `<PLAYER_ID>` should be replaced by the player id
- `<NUMBER_OF_CLAIMED_FIELDS>` should be replaced by the number of fields currently claimed by that player

The player with the most claimed fields wins the game and should be congratulated with the message:

```
\n
Congratulations, Player <PLAYER_ID>! You won!\n
```

where

- `<PLAYER_ID>` should be replaced by the player id.

If there is a tie no congratulations message should be printed.

After that the program should end with the return value `0`.

</details>

## Return Values and Error Messages

The program has to react to errors during the game and print the corresponding error messages and/or return the correct
return values. You can find all error messages that should be printed and all return values in the table below.

Only one error should be printed at once. If multiple errors occur at the same time,
only the highest message in the below table should be printed.

| Return Value | Error Message                                                              | Meaning                                                                                    | Program Phase               |
|--------------|----------------------------------------------------------------------------|--------------------------------------------------------------------------------------------|-----------------------------|
| 0            | -                                                                          | The program terminated successfully                                                        | -                           |
| 1            | `[ERROR] Wrong number of parameters!\n`                                    | The wrong number of command line parameters was entered                                    | Starting the Game           |
| 2            | `[ERROR] Invalid maximum round number!\n`                                  | The entered maximum round number is invalid                                                | Starting the Game           |
| 3            | `[ERROR] Invalid file!\n`                                                  | The config file could not be opened or is invalid                                          | Starting the Game           |
|              | `[ERROR] Entered command not found!\n`                                     | The entered command was not found                                                          | All Commands                |
|              | `[ERROR] Wrong number of parameters for this command!\n`                   | The wrong number of parameters was entered for the specific command                        | All Commands                |
|              | `[ERROR] Entered command is not valid in this phase!\n`                    | The entered command cannot be used in this phase                                           | Command place, Command move |
|              | `[ERROR] Invalid amount! Must be a number > 0!\n`                          | The supplied amount is invalid. Must be an integer and > 0                                 | Command place, Command move |
|              | `[ERROR] Invalid amount! Must be a number <= chips in player inventory!\n` | The supplied amount is invalid. Must be an integer and <= amount of available chips        | Command place               |
|              | `[ERROR] Invalid field!\n`                                                 | The supplied field is invalid, out of range or not claimed by the executing player         | Command place               |
|              | `[ERROR] Invalid origin!\n`                                                | The supplied origin field is invalid, out of bounds or not claimed by the executing player | Command move                |
|              | `[ERROR] Invalid amount! Must be a number <= chips on origin field!\n`     | The supplied amount is invalid. Must be an integer and <= chips on origin field            | Command move                |
|              | `[ERROR] Invalid destination!\n`                                           | The supplied destination field is invalid, out of bounds, out of range or is a water field | Command move                |


## Example Outputs

<details>
<summary><h3>Example Output 1</h3></summary>

The following example output was created using `./a1 2 configs/config_01.txt` to start the program.

```
Welcome to OOPtimal Tactics!
Playing maximum of 2 round(s)!

------------------
Round 1/2 starts!
------------------

------------------
Placement Phase
------------------
  | 1 | 2 | 3 | 4 
1 |A 1|A 1|A 1|   
2 |   |   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |   |B 1|B 1|B 1

Player A, you have 1 chip(s) left, where and how do you want to place your chips?
 > place 1 1 1
  | 1 | 2 | 3 | 4 
1 |A 2|A 1|A 1|   
2 |   |   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |   |B 1|B 1|B 1

Player B, you have 1 chip(s) left, where and how do you want to place your chips?
 > place 1 2 5
  | 1 | 2 | 3 | 4 
1 |A 2|A 1|A 1|   
2 |   |   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |   |B 2|B 1|B 1

------------------
Movement Phase
------------------
  | 1 | 2 | 3 | 4 
1 |A 2|A 1|A 1|   
2 |   |   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |   |B 2|B 1|B 1

Player B, what do you want to do?
 > move 1 2 5 1 5
  | 1 | 2 | 3 | 4 
1 |A 2|A 1|A 1|   
2 |   |   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |B 1|B 1|B 1|B 1

Player A, what do you want to do?
 > move 1 1 1 1 2
  | 1 | 2 | 3 | 4 
1 |A 1|A 1|A 1|   
2 |A 1|   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |B 1|B 1|B 1|B 1

Player B, what do you want to do?
 > pass
Player A, what do you want to do?
 > pass

------------------
Round 2/2 starts!
------------------

------------------
Placement Phase
------------------
  | 1 | 2 | 3 | 4 
1 |A 1|A 1|A 1|   
2 |A 1|   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |B 1|B 1|B 1|B 1

Player B, you have 2 chip(s) left, where and how do you want to place your chips?
 > place 2 1 5
  | 1 | 2 | 3 | 4 
1 |A 1|A 1|A 1|   
2 |A 1|   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |B 3|B 1|B 1|B 1

Player A, you have 2 chip(s) left, where and how do you want to place your chips?
 > place 2 1 2
  | 1 | 2 | 3 | 4 
1 |A 1|A 1|A 1|   
2 |A 3|   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |B 3|B 1|B 1|B 1

------------------
Movement Phase
------------------
  | 1 | 2 | 3 | 4 
1 |A 1|A 1|A 1|   
2 |A 3|   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |B 3|B 1|B 1|B 1

Player A, what do you want to do?
 > help
[ERROR] Entered command not found!
Player A, what do you want to do?
 > pass
Player B, what do you want to do?
 > pass
------------------
GAME END!

Player A claimed 4 field(s)!
Player B claimed 4 field(s)!

```
</details>

<details>
<summary><h3>Example Output 2</h3></summary>

The following example output was created using `./a1 1 configs/config_01.txt` to start the program.

```
Welcome to OOPtimal Tactics!
Playing maximum of 1 round(s)!

------------------
Round 1/1 starts!
------------------

------------------
Placement Phase
------------------
  | 1 | 2 | 3 | 4 
1 |A 1|A 1|A 1|   
2 |   |   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |   |B 1|B 1|B 1

Player A, you have 1 chip(s) left, where and how do you want to place your chips?
 > place 1 1 1
  | 1 | 2 | 3 | 4 
1 |A 2|A 1|A 1|   
2 |   |   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |   |B 1|B 1|B 1

Player B, you have 1 chip(s) left, where and how do you want to place your chips?
 > what
[ERROR] Entered command not found!
Player B, you have 1 chip(s) left, where and how do you want to place your chips?
 > info
Player B:
You have 1 chip(s) saved!
You own 3 field(s)!

Player B, you have 1 chip(s) left, where and how do you want to place your chips?
 > map
Player B, you have 1 chip(s) left, where and how do you want to place your chips?
 > info
Player B:
You have 1 chip(s) saved!
You own 3 field(s)!

Player B, you have 1 chip(s) left, where and how do you want to place your chips?
 > place 1 2 5
------------------
Movement Phase
------------------
Player B, what do you want to do?
 > map
  | 1 | 2 | 3 | 4 
1 |A 2|A 1|A 1|   
2 |   |   |   |   
3 |   |   | ~ | ~ 
4 |   |   | ~ | ~ 
5 |   |B 2|B 1|B 1

Player B, what do you want to do?
 > quit
```
</details>