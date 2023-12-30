// Author: Luka Bradic SV53/2022
// Last update: 27.12.2023.
// About:
// Here is the Sudoku9 class that is uset to play sudoku game.
// It contains methods that are used to load/write board from/to file.
// It contains methods capable of solving, generating and validating sudoku boards.

#pragma once
#include <string>

class Sudoku9 {
public:
	Sudoku9(std::string unsolvedFilename, std::string solvedFilename);
	~Sudoku9();

	/**
	 *
	 * This function is responsible for getting current round number.
	 *
	 * @return number witch represents the current round number.
	 */
	unsigned int getRoundCounter();

	/*
	 This function is responsible for incrementing current round number.
	 */
	void incrementRoundCounter();

	/**
	 *
	 * This function is responsible for getting name of the file containg unsolved sudoku.
	 *
	 * @return name of the file with unsolved board.
	 */
	std::string getUnsolvedFilename();

	/**
	 *
	 * This function is responsible for getting name of the file containg solved sudoku.
	 *
	 * @return name of the file with solved board.
	 */
	std::string getSolvedFilename();

	/**
	 *
	 * This function is responsible for getting name of the file containg solved sudoku grid.
	 *
	 * @param right refference to a variable in which will be placed the number of numbers placed right in sudoku grid.
	 * @param wrong refference to a variable in which will be placed the number of numbers placed wrong in sudoku grid.
	 */
	void getStatistics(int& right, int& wrong);

	int** grid;

	bool backtrack(int** table, int i, int j);
	void readFile(std::string filename, int** table);
	void writeToFile(std::string filename, int** table);
	void generateSudoku(int** table, int removeCount);

	//  Constant representing remove count for level hard
	const int LEVELHARD = 60;

	//  Constant representing remove count for level medium
	const int LEVELMEDIUM = 50;

	//  Constant representing remove count for level easy
	const int LEVELEASY = 30;
private:

	//  Constant representing filename for unolved sudoku
	const std::string unsolvedFilename;

	//  Constant representing filename for solved sudoku
	const std::string solvedFilename;

	// Constant for representing empty cell on board in matrix
	const int EMPTYCELLINT = 0;

	// Constant for representing empty cell when working with file
	const char EMPTYCELLCHAR = '0';

	// Constant for number of ROWS/COLS
	const int DIMENSIONS = 9;


	bool isValidCall(int** table, int i, int j, int val, bool skipPosition);
	int filledInCell(int** table, int i, int j);
	bool meanCellFillingFactor(int** table);
	int random(int l, int h);
	void resetGrid();
	
	// Number of current game round
	unsigned int roundCounter;

	friend class Tests;
};