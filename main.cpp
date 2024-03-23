//----------------------------------------------------------------------------------------------------------------------
// main.cpp
//
// Author: Tutors
//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "Game.hpp"
#include "CommandLine.hpp"
#include "Command.hpp"

enum ReturnValues
{
  SUCCESSFUL = 0,
  WRONG_NUMBER_OF_PARAMETERS = 1,
  INVALID_ROUND_NUMBER = 2,
  INVALID_FILE = 3,
};

//----------------------------------------------------------------------------------------------------------------------
// The main program. Controls the application on a high level view.
// Creates the game and a command line interface, handles the user input and execution of commands.
//
//
// @param argc, argument count, has to be exactly 2
// @param argv, argument vector, contains the name of the csv-file
// @return 0 (SUCCESSFUL), if the application was closed without errors
//         a non-zero number is returned in the case of failure
//
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cout << "[ERROR] Wrong number of parameters!" << std::endl;
    return WRONG_NUMBER_OF_PARAMETERS;
  }

  int rounds = Game::getRoundNumber(argv[1]);
  if (!Game::isValidRoundNumber(rounds))
  {
    std::cout << "[ERROR] Invalid maximum round number!" << std::endl;
    return INVALID_ROUND_NUMBER;
  }

  if (!Game::isValidConfig(argv[2]))
  {
    std::cout << "[ERROR] Invalid file!" << std::endl;
    return INVALID_FILE;
  }
  
  Game game(rounds, argv[2]);
  game.start();

  CommandLine cli;
  while (game.isRunning())
  {
    Command command = cli.readCommand();
    if (command.isQuit())
      break;
    game.execute(command);
  }

  return SUCCESSFUL;
}

