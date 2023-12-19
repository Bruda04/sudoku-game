#pragma once
#include <string>

class Sudoku9 {
public:
	Sudoku9(std::string startFilename, std::string solvedFilename);
	~Sudoku9();

	void readFile(std::string filename);
	void writeToFile(std::string filename);

	unsigned int getRoundCounter();

private:
	int table[9][9];
	unsigned int roundCounter;

	const std::string startFilename;
	const std::string solvedFilename;

	const int emptyCell = -1;
	const char emptyChar = ' ';

};
