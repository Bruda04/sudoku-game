#pragma once
#include "Sudoku9.h"

const unsigned short OPTIONRESTART = 1;
const unsigned short OPTIONEXIT = 2;
const unsigned short OPTIONLOADSUDOKU = 1;
const unsigned short OPTIONGENERATESUDOKU = 2;
const unsigned short OPTIONLOADSOLUTION = 1;
const unsigned short OPTIONSOLVESUDOKU = 2;

const std::string PROMPTCHAR = ">>";

const std::string WELCOMEMESSAGE = "Welcome to Sudokusfera, have a gread time!";

void menuMain(const Sudoku9 &sudoku);

unsigned short dialogLoadFrom();
unsigned short dialogSolver();
unsigned short dialogRestart();
void dialogContinue(std::string filename);

void displayStats(unsigned int roundCount, unsigned int placedBad, unsigned int placedGood);
void displayWelcome();

void clearTerminal();
void pauseDialog();


