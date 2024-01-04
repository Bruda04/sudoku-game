// Author: Luka Bradic SV53/2022
// Last update: 3.1.2024.
// About:
// Here are functions that are used to create menu for the sudoku game.
// It uses Sudoku9 object to maintain the game flow.
  
#pragma once
#include "Sudoku9.h"

// Constants for menu choices

// Menu choice for restart
const unsigned short OPTIONRESTART = 1;
// Menu choice for exit
const unsigned short OPTIONEXIT = 2;
// Menu choice for loading sudoku from file
const unsigned short OPTIONLOADSUDOKU = 1;
// Menu choice for generating sudoku table and placing it in file
const unsigned short OPTIONGENERATESUDOKU = 2;
// Menu choice for loading sudoku solution from file
const unsigned short OPTIONLOADSOLUTION = 1;
// Menu choice for solving the sudoku and placing it in file
const unsigned short OPTIONSOLVESUDOKU = 2;

// Constant for menu prompt character
const std::string PROMPTCHAR = ">>";

// Constant for menu welcome message
const std::string WELCOMEMESSAGE = "Welcome to Sudokusfera, have a great time!";

/**
 * Main menu function for managing the game flow.
 *
 * This function is responsible for creating and managing the flow of the Sudoku game.
 * It allows the user to interact and manipulate the Sudoku game state.
 *
 * @param sudoku A reference to a Sudoku9 object representing the current game state.
 */
void menuMain(Sudoku9& sudoku);

/**
 * This function is responsible for offering and getting the user choice to
 * generate new or load an existing sudoku grid from a file.
 *
 * @return A number which represents the user's choice.
 */
unsigned short dialogLoadFrom();

/**
 * This function is responsible for offering and getting the user choice to
 * let the program solve the sudoku or load the user-generated solution from a file.
 *
 * @return A number which represents the user's choice.
 */
unsigned short dialogSolver();

/**
 * This function is responsible for offering and getting the user choice to
 * let them restart the game or exit.
 *
 * @return A number which represents the user's choice.
 */
unsigned short dialogRestart();

/**
 * This function is responsible for letting the user know which file needs to be edited and
 * wait for the user to give a signal when the file is ready.
 */
void dialogContinue(std::string filename);

/**
 * This function is responsible for showing the user current round statistics.
 *
 * @param roundCount Current round number in the session.
 * @param placedBad Number of badly placed numbers in sudoku.
 * @param placedGood Number of correctly placed numbers in sudoku.
 */
void displayStats(unsigned int roundCount, unsigned int placedBad, unsigned int placedGood);

/**
 * This function is responsible for showing the welcome message to the user.
 */
void displayWelcome();

/**
 * This function is responsible for clearing the terminal screen by going to a new line a couple of times.
 */
void clearTerminal();

/**
 * This function is responsible for pausing the terminal output until the user presses ENTER.
 */
void pauseDialog();
