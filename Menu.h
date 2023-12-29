// Author: Luka Bradic SV53/2022
// Last update: 27.12.2023.
// About:
// Here are functions that are used to create menu for the sudoku game.
// It uses Sudoku9 object to create the game flow.
  
#pragma once
#include "Sudoku9.h"

// Constatns for menu choices

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
const std::string WELCOMEMESSAGE = "Welcome to Sudokusfera, have a gread time!";

/**
 * @brief Main menu function for managing the game flow.
 *
 * This function is responsible for creating and managing the flow of the Sudoku game.
 * It alows the user to interact and manipulate the Sudoku game state.
 *
 * @param sudoku A reference to a Sudoku9 object representing the current game state.
 */
void menuMain(Sudoku9& sudoku);

/**
 *
 * This function is responsible for offeritg and getting the user choice to
 * generate new or load existing sudoku grid from file.
 * 
 * @return number witch represents the user choice
 */
unsigned short dialogLoadFrom();

/**
 *
 * This function is responsible for offeritg and getting the user choice to
 * let the program solve the sudoku or load user generated solution from file.
 *
 * @return number witch represents the user choice
 */
unsigned short dialogSolver();

/**
 *
 * This function is responsible for offeritg and getting the user choice to
 * let the restart game or exit.
 *
 * @return number witch represents the user choice
 */
unsigned short dialogRestart();

/**
 This function is responsible for letting the user know which file needs to be edited and whait for user to give signal when the file is ready.
 */
void dialogContinue(std::string filename);

/**
 * This function is responsible for showing the user current round statistics.
 * 
 * @param roundCount Curent round number in session.
 * @param placedBad Number of badly placed numbers in sudoku.
 * @param placedGood Number of correctly placed numbers in sudoku.
 */
void displayStats(unsigned int roundCount, unsigned int placedBad, unsigned int placedGood);

/**
 * This function is responsible for showing the welcome message to the user.
 */
void displayWelcome();

/**
* This function is responsible for clearing the terminal screen by going to new line a couple of times.
*/
void clearTerminal();

/**
* This function is responsible for pausing the terminal output until user presses ENTER.
*/
void pauseDialog();


