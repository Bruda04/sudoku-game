#include "Sudoku9.h"
#include <fstream>
#include <iostream>
#include <cstdlib> 

Sudoku9::Sudoku9(std::string unsolvedFilename, std::string solvedFilename) :
	unsolvedFilename(unsolvedFilename),
	solvedFilename(solvedFilename),
	roundCounter(0)
	{

	grid = new int* [DIMENSIONS];
	for (int i = 0; i < DIMENSIONS; ++i) {
		grid[i] = new int[DIMENSIONS];

		for (int j = 0; j < DIMENSIONS; ++j) {
			grid[i][j] = EMPTYCELLINT;
		}
	}

	writeToFile(unsolvedFilename, grid);
	writeToFile(solvedFilename, grid);

	srand(time(0));
}

Sudoku9::~Sudoku9() {
	for (int i = 0; i < DIMENSIONS; ++i) {
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
		for (int j = 0; j < DIMENSIONS; ++j) {
			if (line[j] == EMPTYCELLCHAR) {
				number = EMPTYCELLINT;
			} else {
				char c = line[j];
				number = std::atoi(&c);
			}

			table[i][j] = number;
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
		for (int j = 0; j < DIMENSIONS; ++j) {
			if (table[i][j] == EMPTYCELLINT) {
				outputFile << EMPTYCELLCHAR;
			}
			else {
				outputFile << table[i][j];
			}
		}
		outputFile << std::endl;
	}

    outputFile.close();
}

int Sudoku9::random(int l, int h) {
	return (rand() % (h - l + 1)) + l;
}

void Sudoku9::resetGrid() {
	for (int i = 0; i < DIMENSIONS; ++i) {
		for (int j = 0; j < DIMENSIONS; ++j) {
			grid[i][j] = EMPTYCELLINT;
		}
	}
}

void Sudoku9::generateSudoku(int** table, int removeCount) {
	int pivotRow[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,};

	for (int i = 0; i < DIMENSIONS; ++i) {
		int newIndex = random(0, 8);
		int oldVal = pivotRow[newIndex];
		pivotRow[newIndex] = pivotRow[i];
		pivotRow[i] = oldVal;
	}

	for (int i = 0; i < DIMENSIONS; ++i) {
		table[0][i] = pivotRow[i];
	}

	backtrack(table, 0, 0);

	while (removeCount != 0) {
		int i = random(0, 8);
		int j = random(0, 8);

		int oldVal = table[i][j];

		if (oldVal == EMPTYCELLINT) {
			continue;
		}

		table[i][j] = EMPTYCELLINT;
		removeCount--;
		continue;

	}

	if (!meanCellFillingFactor(table)) {
		for (int i = 0; i < DIMENSIONS; ++i) {
			for (int j = 0; j < DIMENSIONS; ++j) {
				table[i][j] = EMPTYCELLINT;
			}
		}
		generateSudoku(table, removeCount);
	}
	
}


bool Sudoku9::backtrack(int** table, int i, int j) {
	if (i == DIMENSIONS) {
		return true;
	} else if (j == DIMENSIONS) {
		return backtrack(table, i + 1, 0);
	} else if (table[i][j] != EMPTYCELLINT) {
		return backtrack(table, i, j + 1);
	} else {
		for (int val = 1; val < 10; val++) {
			if (isValidCall(table, i, j, val, false)) {
				table[i][j] = val;
				if (backtrack(table, i, j+1)) {
					return true;
				}
				table[i][j] = EMPTYCELLINT;
			}
		}

		return false;
	}
}

bool Sudoku9::isValidCall(int** table, int i, int j, int val, bool skipPosition) {
	int block_i = i / 3;
	int block_j = j / 3;

	for (int bi = block_i*3; bi < block_i*3+3; ++bi) {
		for (int bj = block_j * 3; bj < block_j * 3 + 3; ++bj) {
			if (table[bi][bj] == val) {
				if (skipPosition && bi == i && bj == j) {
					continue;
				}
				return false;
			}
		}
	}

	for (int ci = 0; ci < DIMENSIONS; ++ci) {
		if (table[i][ci] == val) {
			if (skipPosition && ci == j) {
				continue;
			}
			return false;		
		}
	}

	for (int ri = 0; ri < DIMENSIONS; ri++) {
		if (table[ri][j] == val) {
			if (skipPosition && ri == i) {
				continue;
			}
			return false;
		}
	}

	return true;
}

int Sudoku9::filledInCell(int** table, int i, int j) {
	int n = 0;

	int block_i = i / 3;
	int block_j = j / 3;

	for (int bi = block_i * 3; bi < block_i * 3 + 3; ++bi) {
		for (int bj = block_j * 3; bj < block_j * 3 + 3; ++bj) {
			if (table[bi][bj] != EMPTYCELLINT) {
				n++;
			}
		}
	}

	return n;
}

bool Sudoku9::meanCellFillingFactor(int** table) {
	double sum = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (filledInCell(table, i * 3, j * 3) > 6) {
				return false;
			}
		}
	}

	return true;
}

void Sudoku9::getStatistics(int& good, int& bad) {
	int** table = grid;
	good = 0;
	bad = 0;
	for (int i = 0; i < DIMENSIONS; i++) {
		for (int j = 0; j < DIMENSIONS; j++) {
			if (isValidCall(table, i, j, table[i][j], true)) {
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
