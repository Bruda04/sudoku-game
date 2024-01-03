// Author: Luka Bradic SV53/2022
// Last update: 2.1.2024.
// About:
// Here is the Sudoku9 class that is uset to play sudoku game.
// It contains methods that are used to load/write board from/to file.
// It contains methods capable of solving, generating and validating sudoku boards.

#pragma once
#include <string>

class Sudoku9 {
public:

	/**
	 * Constructor for the Sudoku9 object used to play sudoku game.
	 * 
	 * @param unsolvedFilename Name of the file where the sudoku puzzle will be placed.
	 * @param unsolvedFilename Name of the file where the sudoku solution will be placed.
	 */
	Sudoku9(std::string unsolvedFilename, std::string solvedFilename);

	/**
	 * Destructor for the Sudoku9 object.
	 */
	~Sudoku9();

	// Pointer to matrix representing sudoku grid 
	int** grid;

	/**
	 * This function is responsible for parsing sudoku grid from file and filling the matrix.
	 *
	 * @param filename Name of the file to read from.
	 * @param table Pointer to a matrix with sudoku.
	 * 
	 * @return If number if any position was different in table and file
	 */
	bool readFile(std::string filename, int** table);

	/**
	 * This function is responsible for writing sudoku grid into the file from the matrix.
	 *
	 * @param filename Name of the file to write to.
	 * @param table Pointer to a matrix with sudoku.
	 */
	void writeToFile(std::string filename, int** table);

	/**
	 * This function is responsible for handling the bactracking algorithm used to solve the sudoku.
	 *
	 * @param table Pointer to a matrix with sudoku.
	 * @param i Row index (0 if starting from beginning).
	 * @param j Column index (0 if starting from beginning).
	 */
	bool backtrack(int** table, int i, int j);

	/**
	 * This function is responsible for generating sudoku puzzle with specified amount of filled numbers.
	 *
	 * @param table Pointer to a matrix with sudoku.
	 * @param removeCount Amount of numbers to remove from solved sudoku.
	 */
	void generateSudoku(int** table, int removeCount);

	/**
	 * This function is responsible for getting the current round number.
	 *
	 * @return A number which represents the current round number.
	 */
	unsigned int getRoundCounter();

	/*
	 * This function is responsible for incrementing the current round number.
	 */
	void incrementRoundCounter();

	/**
	 * This function is responsible for getting the name of the file containing unsolved sudoku.
	 *
	 * @return The name of the file with the unsolved board.
	 */
	std::string getUnsolvedFilename();

	/**
	 * This function is responsible for getting the name of the file containing solved sudoku.
	 *
	 * @return The name of the file with the solved board.
	 */
	std::string getSolvedFilename();

	/*
	 * This function is responsible for displaying the sudoku grid in the terminal.
	 *
	 * @param table Pointer to a matrix with sudoku.
	 */
	void displayGrid(int** table);

	/**
	 * This function is responsible for getting the name of the file containing solved sudoku grid.
	 *
	 * @param table Pointer to a matrix with sudoku.
	 * @param right Reference to a variable in which the number of numbers placed correctly in the sudoku grid will be placed.
	 * @param wrong Reference to a variable in which the number of numbers placed incorrectly in the sudoku grid will be placed.
	 */
	void getStatistics(int** table, int& right, int& wrong);

	// Constant representing remove count for level hard
	const int LEVELHARD = 60;

	// Constant representing remove count for level medium
	const int LEVELMEDIUM = 50;

	// Constant representing remove count for level easy
	const int LEVELEASY = 30;

private:

	// Constant representing filename for unolved sudoku
	const std::string unsolvedFilename;

	// Constant representing filename for solved sudoku
	const std::string solvedFilename;

	// Constant for representing empty cell on board in matrix
	const int EMPTYCELLINT = 0;

	// Constant for representing empty cell when working with file
	const char EMPTYCELLCHAR = '0';

	// Constant for number of ROWS/COLS
	const int DIMENSIONS = 9;

	/*
	 * This function is responsible for checking if the value placed in a certain position is against the sudoku rules.
	 *
	 * @param table Pointer to a matrix with sudoku.
	 * @param i Row index.
	 * @param j Column index.
	 * @param val Number to check.
	 * @param skipPosition Flag to skip [i][j] position if the value is already placed.
	 *
	 * @return If the rules are met or not.
	 */
	bool isValidMove(int** table, int i, int j, int val, bool skipPosition);

	/**
	 * This function is responsible for counting how many numbers are filled in a 3x3 cell.
	 *
	 * @param table Pointer to a matrix with sudoku.
	 * @param i 3x3 Cell row index.
	 * @param j 3x3 Cell column index.
	 *
	 * @return Number of filled numbers in a 3x3 cell.
	 */
	int filledInCell(int** table, int i, int j);

	/**
	 * This function is responsible for checking if any of the 3x3 cells has more than 6 numbers filled.
	 *
	 * @param table Pointer to a matrix with sudoku.
	 *
	 * @return If the condition is satisfied.
	 */
	bool meanCellFillingFactor(int** table);

	/**
	 * This function is responsible for generating a random value in the range [l, h].
	 *
	 * @param l Representing the lower bound.
	 * @param h Representing the upper bound.
	 *
	 * @return A random number in the given range.
	 */
	int random(int l, int h);

	/**
	 * This function is responsible for setting every position in the matrix grid to EMPTYCELLINT.
	 * 
	 * @param table Pointer to a matrix with sudoku.
	 */
	void resetGrid(int** table);

	// Number of the current game round
	unsigned int roundCounter;

	// Marking the Tests class used to test Sudoku9 as a friend
	friend class Tests;
};