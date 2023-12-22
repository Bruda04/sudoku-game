#include "Sudoku9.h"
#include <fstream>
#include <iostream>

Sudoku9::Sudoku9(std::string unsolvedFilename, std::string solvedFilename):
	unsolvedFilename(unsolvedFilename),
	solvedFilename(solvedFilename),
	roundCounter(0) {

	unsolved = new int* [9];
	for (int i = 0; i < 9; ++i) {
		unsolved[i] = new int[9];
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			unsolved[i][j] = emptyCell;
		}
	}

	solved = new int* [9];
	for (int i = 0; i < 9; ++i) {
		solved[i] = new int[9];
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			solved[i][j] = emptyCell;
		}
	}
}

Sudoku9::~Sudoku9() {
	for (int i = 0; i < 9; ++i) {
		delete[] unsolved[i];
	}
	delete[] unsolved;

	for (int i = 0; i < 9; ++i) {
		delete[] solved[i];
	}

	delete[] solved;
}

void Sudoku9::readFile(std::string filename, int** table) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return;
    }

    std::string line = "";
	int number = 0;
    for (int i = 0; i < 9; ++i) {
		std::getline(inputFile, line);
		for (int j = 0; j < 9; ++j) {
			if (line[j] == emptyChar) {
				number = emptyCell;
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

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (table[i][j] == emptyCell) {
				outputFile << emptyChar;
			}
			else {
				outputFile << table[i][j];
			}
		}
		outputFile << std::endl;
	}

    outputFile.close();
}

unsigned int Sudoku9::getRoundCounter() {
	return roundCounter;
}

void Sudoku9::incrementRoundCounter() {
	roundCounter++;
}

bool Sudoku9::backtrack(int** copyTable, int i, int j) {
	if (i == 9) {
		return true;
	} else if (j == 9) {
		return backtrack(copyTable, i + 1, 0);
	} else if (copyTable[i][j] != emptyCell) {
		return backtrack(copyTable, i, j + 1);
	} else {
		for (int val = 1; val < 10; val++) {
			if (isValidCall(copyTable, i, j, val, false)) {
				copyTable[i][j] = val;
				if (backtrack(copyTable, i, j+1)) {
					return true;
				}
				copyTable[i][j] = emptyCell;
			}
		}

		return false;
	}
}

bool Sudoku9::isValidCall(int** originalTable, int i, int j, int val, bool skipPosition) {
	int block_i = i / 3;
	int block_j = j / 3;

	for (int bi = block_i*3; bi < block_i*3+3; ++bi) {
		for (int bj = block_j * 3; bj < block_j * 3 + 3; ++bj) {
			if (originalTable[bi][bj] == val) {
				if (skipPosition && bi == i && bj == j) {
					continue;
				}
				return false;
			}
		}
	}

	for (int ci = 0; ci < 9; ++ci) {
		if (originalTable[i][ci] == val) {
			if (skipPosition && ci == j) {
				continue;
			}
			return false;		
		}
	}

	for (int ri = 0; ri < 9; ri++) {
		if (originalTable[ri][j] == val) {
			if (skipPosition && ri == i) {
				continue;
			}
			return false;
		}
	}

	return true;
}

int** Sudoku9::copyArray(int** original) {
	int** newArray = new int* [9];
	for (int i = 0; i < 9; ++i) {
		newArray[i] = new int[9];
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			newArray[i][j] = original[i][j];
		}
	}

	return newArray;
}

void Sudoku9::destroyArray(int** original) {
	for (int i = 0; i < 9; ++i) {
		delete[] original[i];
	}
	delete[] original;
}

void Sudoku9::getStatistics(int& good, int& bad) {
	int** table = unsolved;
	good = 0;
	bad = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
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

