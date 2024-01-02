#pragma once
#include "Sudoku9.h"

class Tests {
public:

	/**
	 * Constructor for the Tests object used to test Sudoku9 class.
	 *
	 * @param sudoku Pointer to a Sudoku9 object used for testing.
	 */
	Tests(Sudoku9* sudoku);

	/**
	 * Destructor for the Tests object.
	 */
	~Tests();

	/**
	 * This function is responsible for running all the tests and showing the output.
	 */
	void testMain();

private:

	// Sudoku9 pointer used for testing
	Sudoku9* sudoku;

	// Name of the file used to test read/write functions. 
	const std::string testFileName = "testFile.txt";

	/**
	 * This function is responsible for displaying currently running test.
	 */
	void displayTestName(std::string testName);
	
	/**
	 * This function is responsible for setting the Sudoku9 grid to passed values.
	 * 
	 * @param newGrid Values to be placed in Sudoku9 grid.
	 */
	void setGridValues(std::string newGrig[]);

	/**
	 * This function is responsible for testing the Sudoku9 random method.
	 *
	 * @return If the tests has passed or not.
	 */
	bool testRandom();

	/**
	 * This function is responsible for testing the Sudoku9 getStatistics method.
	 *
	 * @return If the tests has passed or not.
	 */
	bool testGetStatistics();

	/**
	 * This function is responsible for testing the Sudoku9 filledInCell method.
	 *
	 * @return If the tests has passed or not.
	 */
	bool testFilledInCell();

	/**
	 * This function is responsible for testing the Sudoku9 resetGrid method.
	 *
	 * @return If the tests has passed or not.
	 */
	bool testResetGrid();

	/**
	 * This function is responsible for testing the Sudoku9 meanCellFIllingFactor method.
	 *
	 * @return If the tests has passed or not.
	 */
	bool testMeanCellFillingFactor();

	/**
	 * This function is responsible for testing the Sudoku9 readFile and writeToFile methods.
	 *
	 * @return If the tests has passed or not.
	 */
	bool testReadWriteFile();

	/**
	 * This function is responsible for testing the Sudoku9 backtrack method.
	 *
	 * @return If the tests has passed or not.
	 */
	bool testBacktrack();

	/**
	 * This function is responsible for testing the Sudoku9 generateSudoku method.
	 *
	 * @return If the tests has passed or not.
	 */
	bool testGenerateSudoku();

};
