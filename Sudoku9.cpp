#include "Sudoku9.h"
#include <fstream>
#include <iostream>

Sudoku9::Sudoku9(std::string startFilename, std::string solvedFilename): 
	startFilename(startFilename),
	solvedFilename(solvedFilename),
	roundCounter(0) {

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			table[i][j] = emptyCell;
		}
	}
}

Sudoku9::~Sudoku9() {
}

void Sudoku9::readFile(std::string filename) {
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
				number = std::atoi(&line[j]);
			}

			table[i][j] = number;
		}
    }
    

    inputFile.close();
}

void Sudoku9::writeToFile(std::string filename) {
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
