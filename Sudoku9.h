#pragma once
#include <string>

class Sudoku9 {
public:

	Sudoku9(std::string unsolvedFilename, std::string solvedFilename);
	~Sudoku9();


	unsigned int getRoundCounter();
	void incrementRoundCounter();

	int** copyArray(int** original);
	void destroyArray(int** original);

	void getStatistics(int& right, int& wrong);

	std::string getUnsolvedFilename();
	std::string getSolvedFilename();

	int** unsolved;
	int** solved;

	bool backtrack(int** table, int i, int j);
	void readFile(std::string filename, int** table);
	void writeToFile(std::string filename, int** table);
private:
	const std::string unsolvedFilename;
	const std::string solvedFilename;

	const int emptyCell = 0;
	const char emptyChar = '0';

	bool isValidCall(int** table, int i, int j, int val, bool skipPosition);

	unsigned int roundCounter;

};