#include "Sudoku9.h"
#include <fstream>
#include <iostream>
#include <cstdlib> 

Sudoku9::Sudoku9(std::string unsolvedFilename, std::string solvedFilename) :
	unsolvedFilename(unsolvedFilename),
	solvedFilename(solvedFilename),
	roundCounter(0)
	{

	grid = new int* [DIMENSIONS]; // making 2D array
	for (int i = 0; i < DIMENSIONS; ++i) {
		grid[i] = new int[DIMENSIONS];

		for (int j = 0; j < DIMENSIONS; ++j) {
			grid[i][j] = EMPTYCELLINT; // setting every position to empty value
		}
	}

	// creating files for puzzle and solution
	writeToFile(unsolvedFilename, grid);
	writeToFile(solvedFilename, grid);

	srand(time(0)); // setting seed for pseudo random function
}

Sudoku9::~Sudoku9() {
	for (int i = 0; i < DIMENSIONS; ++i) { // dealocating all memory that was created with object
		delete[] grid[i];
	}
	delete[] grid;
}

void Sudoku9::readFile(std::string filename, int** table) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return;
    }

    std::string line = "";
	int number = 0;

    for (int i = 0; i < DIMENSIONS; ++i) { 
		std::getline(inputFile, line);

		if (i % 3 == 0 && i != 0) { // if row with "-" => skip
			std::getline(inputFile, line);
		}

		// looping through 3 row segments split by "|"
		int correction = 0; // adding one position for every "|" passed
		for (int j = 0; j < DIMENSIONS / 3; ++j) {
			for (int k = 0; k < DIMENSIONS / 3; k++) {
				int p = j * 3 + k + correction; // segment * 3 + positionInSegment + correction
				if (line[p] == EMPTYCELLCHAR) {
					number = EMPTYCELLINT; // if empty
				} else {
					char c = line[p];
					number = c - '0'; // if not empty convert from char to int
				}

				table[i][j*3+k] = number; // set the value (segment * 3 + positionInSegment)
			}

			correction++;

		}
    }
    

    inputFile.close();
}

void Sudoku9::writeToFile(std::string filename, int** table) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }

	for (int i = 0; i < DIMENSIONS; ++i) {
		// splitting every 3 rows
		if (i % 3 == 0 && i != 0) { // if row with "-"
			outputFile << "-----------" << std::endl;
		}

		for (int j = 0; j < DIMENSIONS; ++j) {
			// splitting every 3 cols
			if (j % 3 == 0 && j != 0) { // if position in row with "|"
				outputFile << "|";
			}

			if (table[i][j] == EMPTYCELLINT) {
				outputFile << EMPTYCELLCHAR; // if empty
			}
			else {
				outputFile << table[i][j]; // if not empty
			}
		}

		outputFile << std::endl;
	}

    outputFile.close();
}

int Sudoku9::random(int l, int h) {
	return (rand() % (h - l + 1)) + l; // placing randomly generated number in scope [l, h]
}

void Sudoku9::resetGrid(int** table) {
	for (int i = 0; i < DIMENSIONS; ++i) {
		for (int j = 0; j < DIMENSIONS; ++j) {
			table[i][j] = EMPTYCELLINT;
		}
	}
}

void Sudoku9::displayGrid(int** table) {
	for (int i = 0; i < DIMENSIONS; ++i) {
		// splitting every 3 rows
		if (i % 3 == 0 && i != 0) { // if row with "-"
			std::cout << "-----------" << std::endl;
		}
		
		for (int j = 0; j < DIMENSIONS; ++j) {
			// splitting every 3 cols
			if (j % 3 == 0 && j != 0) { // if position in row with "|"
				std::cout << "|";
			}
			std::cout << table[i][j];
		}

		std::cout << std::endl;
	}
}

void Sudoku9::generateSudoku(int** table, int removeCount) {
	resetGrid(table);

	int pivotRow[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,}; // all values in first row

	for (int i = 0; i < DIMENSIONS; ++i) { // shuffle the pivot row
		int newIndex = random(0, 8);
		int oldVal = pivotRow[newIndex];

		pivotRow[newIndex] = pivotRow[i];
		pivotRow[i] = oldVal;
	}

	for (int i = 0; i < DIMENSIONS; ++i) { // set values in first row from pivot row
		table[0][i] = pivotRow[i];
	}

	backtrack(table, 0, 0); // fill the puzzle to the end

	while (removeCount != 0) { // remove numbers from the solution
		// random position
		int i = random(0, 8);
		int j = random(0, 8);

		int oldVal = table[i][j]; // saving the old value

		if (oldVal == EMPTYCELLINT) { // if already removed
			continue;
		}

		table[i][j] = EMPTYCELLINT; // remove number
		removeCount--;
		continue;

	}

	if (!meanCellFillingFactor(table)) { // if mean filling factor of 6 not satisfied
		generateSudoku(table, removeCount); // generate again
	}
	
}


bool Sudoku9::backtrack(int** table, int i, int j) {
	if (i == DIMENSIONS) { // passed the last row = end
		return true;
	} else if (j == DIMENSIONS) { // end of the row
		return backtrack(table, i + 1, 0); // go to the next row
	} else if (table[i][j] != EMPTYCELLINT) { // number already set
		return backtrack(table, i, j + 1); // go to next position in row
	} else {
		for (int val = 1; val < 10; val++) { // loop throuh all possible number values
			if (isValidMove(table, i, j, val, false)) { // if val can be placed there
				table[i][j] = val;

				if (backtrack(table, i, j+1)) { // go to next position in row and if placed good
					return true;
				}

				// reset the previously set val if it led to unsolvable scenario
				table[i][j] = EMPTYCELLINT; 
			}
		}

		return false; // got to unsovable state
	}
}

bool Sudoku9::isValidMove(int** table, int i, int j, int val, bool skipPosition) {
	// calculating the 3x3 cell index
	int blockI = i / 3;
	int blockJ = j / 3;

	for (int bi = blockI*3; bi < blockI*3+3; ++bi) { // looping through 3x3 cell
		for (int bj = blockJ * 3; bj < blockJ * 3 + 3; ++bj) {
			if (table[bi][bj] == val) { // if there is duplicate value in 3x3 cell
				if (skipPosition && bi == i && bj == j) { // skip position if value is already placed
					continue;
				}
				return false;
			}
		}
	}

	for (int ci = 0; ci < DIMENSIONS; ++ci) { // looping through row
		if (table[i][ci] == val) { // if there is duplicate value in row
			if (skipPosition && ci == j) { // skip position if value is already placed
				continue;
			}
			return false;		
		}
	}

	for (int ri = 0; ri < DIMENSIONS; ri++) {
		if (table[ri][j] == val) { // if there is duplicate value in column
			if (skipPosition && ri == i) { // skip position if value is already placed
				continue;
			}
			return false;
		}
	}

	return true;
}

int Sudoku9::filledInCell(int** table, int i, int j) {
	int n = 0;

	for (int bi = i * 3; bi < i * 3 + 3; ++bi) { // looping through every position in 3x3 cell with index [i][j]
		for (int bj = j * 3; bj < j * 3 + 3; ++bj) {
			if (table[bi][bj] != EMPTYCELLINT) { // incrementing counter if number is set in position
				n++;
			}
		}
	}

	return n;
}

bool Sudoku9::meanCellFillingFactor(int** table) {
	for (int i = 0; i < 3; ++i) { // looping through all 3x3 cells
		for (int j = 0; j < 3; ++j) {
			// if 3x3 cell has more than 6 filled numbers filling factor is not satified
			if (filledInCell(table, i, j) > 6) {
				return false;
			}
		}
	}

	return true;
}

void Sudoku9::getStatistics(int** table, int& good, int& bad) {
	good = 0;
	bad = 0;

	for (int i = 0; i < DIMENSIONS; i++) {
		for (int j = 0; j < DIMENSIONS; j++) {
			// if the number in position [i][j] meet the game rules
			if (isValidMove(table, i, j, table[i][j], true)) {
				good++;
			} else {
				bad++;
			}
		}
	}
}

std::string Sudoku9::getUnsolvedFilename() {
	return unsolvedFilename;
}

std::string Sudoku9::getSolvedFilename() {
	return solvedFilename;
}

unsigned int Sudoku9::getRoundCounter() {
	return roundCounter;
}

void Sudoku9::incrementRoundCounter() {
	roundCounter++;
}
