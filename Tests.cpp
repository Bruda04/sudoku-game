#include "Tests.h"
#include <iostream>

Tests::Tests(Sudoku9* sudokuRef): sudoku(sudokuRef) {
}

Tests::~Tests() {
}


void Tests::testMain() {
	std::cout << "Tests for the sudoku class" << std::endl;

    displayTestName("int Sudoku9::random(int l, int h)");
    testRandom();

    displayTestName("void Sudoku9::getStatistics(int& good, int& bad)");
    testGetStatistics();

    displayTestName("int Sudoku9::filledInCell(int** table, int i, int j)");
    testGetStatistics();

    displayTestName("void Sudoku9::resetGrid()");
    testResetGrid();

    displayTestName("bool Sudoku9::meanCellFillingFactor(int** table)");
    testResetGrid();

    return;
}

void Tests::displayTestName(std::string testName) {
    std::cout << std::endl;
    std::cout << "===================================================================" << std::endl;
    std::cout << "Tesing " << testName << std::endl;
    std::cout << "===================================================================" << std::endl;
}

void Tests::setGridValues(std::string newGrig[]) {
    for (int i = 0; i < DIMENSIONS; ++i) {
        for (int j = 0; j < DIMENSIONS; ++j) {
            char c = newGrig[i][j];
            int number = std::atoi(&c);
            sudoku->grid[i][j] = number;
        }
    }
}

bool Tests::testRandom() {
    const int lowerBound = 1;
    const int upperBound = 100;

    const int numIterations = 1000000;

    for (int i = 0; i < numIterations; ++i) {
        int result = sudoku -> random(lowerBound, upperBound);
        if (result < lowerBound || result > upperBound) {
            std::cout << "Test failed: Value out of range!" << std::endl;
            return false;
        }
    }

    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testGetStatistics() {
    sudoku -> resetGrid();

    int actualGood, actualBad;
    int expectedGood;
    int expectedBad;

    std::string allWrong[9] = {
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000"
    };
    setGridValues(allWrong);

    expectedGood = 0;
    expectedBad = 81;

    sudoku->getStatistics(actualGood, actualBad);

    if (actualGood != expectedGood || actualBad != expectedBad) {
        std::cout << "Test failed: Expected all bad!" << std::endl;
        return false;
    }

    std::string allGood[9] = {
        "125368479",
        "734259168",
        "689174235",
        "216435897",
        "357891624",
        "498726513",
        "961587342",
        "843912756",
        "572643981"
    };
    setGridValues(allGood);

    expectedGood = 81;
    expectedBad = 0;

    sudoku->getStatistics(actualGood, actualBad);

    if (actualGood != expectedGood || actualBad != expectedBad) {
        std::cout << "Test failed: Expected all good!" << std::endl;
        return false;
    }


    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testFilledInCell() {
    sudoku->resetGrid();

    int actualFilled;
    int expectedFilled;

    std::string filled0[9] = {
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000"
    };
    setGridValues(filled0);

    expectedFilled = 0;

    actualFilled = sudoku->filledInCell(sudoku->grid, 0, 0);

    if (expectedFilled != actualFilled) {
        std::cout << "Test failed: No cells filled!" << std::endl;
        return false;
    }

    std::string filled9[9] = {
        "125368479",
        "734259168",
        "689174235",
        "216435897",
        "357891624",
        "498726513",
        "961587342",
        "843912756",
        "572643981"
    };

    setGridValues(filled9);

    expectedFilled = 9;

    actualFilled = sudoku->filledInCell(sudoku->grid, 8, 8);


    if (actualFilled != expectedFilled) {
        std::cout << "Test failed: All cells should be filled!" << std::endl;
        return false;
    }

    std::string filled5[9] = {
        "000000000",
        "055000000",
        "666600000",
        "123600000",
        "040600000",
        "005600000",
        "666600000",
        "000000000",
        "000000000"
    };
    setGridValues(filled5);

    expectedFilled = 5;

    actualFilled = sudoku->filledInCell(sudoku->grid, 1, 0);

    if (expectedFilled != actualFilled) {
        std::cout << "Test failed: Overflow cells counted" << std::endl;
        return false;
    }


    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testResetGrid() {
    sudoku->resetGrid();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (true) {
                if (sudoku->grid[i][j] != sudoku->EMPTYCELLINT) {
                    std::cout << "Test failed: Found cell with value != empty value" << std::endl;
                    return false;
                }
            }
        }
    }


    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testMenaCellFillingFactor() {
    sudoku->resetGrid();

    int actualStatus;
    int expectedStatus;

    std::string statusTrue[9] = {
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000"
    };
    setGridValues(statusTrue);

    expectedStatus = true;

    actualStatus = sudoku->meanCellFillingFactor(sudoku->grid);

    if (actualStatus != expectedStatus) {
        std::cout << "Test failed: No cells filled" << std::endl;
        return false;
    }

    std::string statusFalse[9] = {
        "104900000",
        "720900000",
        "653900000",
        "999900000",
        "000000000",
        "000000000",
        "000000000",
        "000000000",
        "000000000"
    };
    setGridValues(statusFalse);

    expectedStatus = false;

    actualStatus = sudoku->meanCellFillingFactor(sudoku->grid);

    if (actualStatus != expectedStatus) {
        std::cout << "Test failed: Cells not counted" << std::endl;
        return false;
    }

    std::cout << "Test passed!" << std::endl;
    return true;
}


