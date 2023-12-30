#pragma once
#include "Sudoku9.h"

class Tests {
public:
	Tests(Sudoku9* sudoku);
	~Tests();

	void testMain();

private:

	Sudoku9* sudoku;
	const int DIMENSIONS = 9;

	void displayTestName(std::string testName);
	void setGridValues(std::string newGrig[]);

	bool testRandom();
	bool testGetStatistics();
	bool testFilledInCell();
	bool testResetGrid();
	bool testMenaCellFillingFactor();

};
