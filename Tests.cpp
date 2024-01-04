#include "Tests.h"
#include <iostream>

Tests::Tests(Sudoku9* sudokuRef): sudoku(sudokuRef) {
}

Tests::~Tests() {
}


void Tests::testMain() {
	std::cout << "Tests for the Sudoku9 class" << std::endl;

    displayTestName("int Sudoku9::random(int l, int h)");
    testRandom();

    displayTestName("void Sudoku9::getStatistics(int& good, int& bad)");
    testGetStatistics();

    displayTestName("int Sudoku9::filledInCell(int** table, int i, int j)");
    testFilledInCell();

    displayTestName("bool Sudoku9::meanCellFillingFactor(int** table)");
    testMeanCellFillingFactor();

    displayTestName("void Sudoku9::resetGrid(sudoku->grid)");
    testResetGrid();

    displayTestName("\nvoid Sudoku9::writeToFile(std::string filename, int** table)\nvoid Sudoku9::readFile(std::string filename, int** table)");
    testReadWriteFile();

    displayTestName("bool Sudoku9::backtrack(int** table, int i, int j)");
    testBacktrack();

    displayTestName("void generateSudoku(int** table, int removeCount)");
    testGenerateSudoku();

    return;
}

void Tests::displayTestName(std::string testName) {
    std::cout << std::endl;
    std::cout << "===================================================================" << std::endl;
    std::cout << "Tesing " << testName << std::endl;
    std::cout << "===================================================================" << std::endl;
}

void Tests::setGridValues(std::string newGrig[]) {
    for (int i = 0; i < sudoku->DIMENSIONS; ++i) {
        for (int j = 0; j < sudoku->DIMENSIONS; ++j) {
            char c = newGrig[i][j];
            int number = c - '0'; // converting from char to int

            sudoku->grid[i][j] = number; // setting the number in grid
        }
    }
}

bool Tests::testRandom() {
    const int lowerBound = 1;
    const int upperBound = 100;

    const int numIterations = 1000000;

    for (int i = 0; i < numIterations; ++i) {
        int result = sudoku -> random(lowerBound, upperBound); // generating random number

        if (result < lowerBound || result > upperBound) { // if outside scope test fails
            std::cout << "Test failed: Value out of range!" << std::endl;
            return false;
        }
    }

    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testGetStatistics() {
    sudoku -> resetGrid(sudoku->grid);

    int actualGood;
    int actualBad;
    int expectedGood;
    int expectedBad;

    // testing with empty grid
    std::string allWrong[] = {
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

    sudoku->getStatistics(sudoku->grid, actualGood, actualBad);

    if (actualGood != expectedGood || actualBad != expectedBad) {
        std::cout << "Test failed: Expected all bad!" << std::endl;
        return false;
    }

    // testing with good solution
    std::string allGood[] = {
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

    sudoku->getStatistics(sudoku->grid, actualGood, actualBad);

    if (actualGood != expectedGood || actualBad != expectedBad) {
        std::cout << "Test failed: Expected all good!" << std::endl;
        return false;
    }

    // testing with good solution
    std::string mixed[] = {
        "125368479",
        "734259168",
        "639171535",
        "216435797",
        "355890624",
        "498726513",
        "960787342",
        "841912756",
        "972644981"
    };
    setGridValues(mixed);

    expectedGood = 55;
    expectedBad = 26;

    sudoku->getStatistics(sudoku->grid, actualGood, actualBad);

    if (actualGood != expectedGood || actualBad != expectedBad) {
        std::cout << "Test failed: Expected 55 good and 26 bad!" << std::endl;
        return false;
    }


    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testFilledInCell() {
    sudoku->resetGrid(sudoku->grid);

    int actualFilled;
    int expectedFilled;

    //testing no filled
    std::string filled0[] = {
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

    // testing all filled
    std::string filled9[] = {
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

    actualFilled = sudoku->filledInCell(sudoku->grid, 2, 2);


    if (actualFilled != expectedFilled) {
        std::cout << "Test failed: All cells should be filled!" << std::endl;
        return false;
    }

    // testing for 3x3cell overflow
    std::string filled5[] = {
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
    std::string filled81[] = {
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

    setGridValues(filled81);

    sudoku->resetGrid(sudoku->grid);

    for (int i = 0; i < sudoku->DIMENSIONS; ++i) {
        for (int j = 0; j < sudoku->DIMENSIONS; ++j) {
            if (sudoku->grid[i][j] != sudoku->EMPTYCELLINT) { // if number not reset
                std::cout << "Test failed: Found cell with value not equal empty value" << std::endl;
                return false;
            }
        }
    }

    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testMeanCellFillingFactor() {
    sudoku->resetGrid(sudoku->grid);

    int actualStatus;
    int expectedStatus;

    // testing empty grid
    std::string statusTrue[] = {
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

    // testing more than 6 filled
    std::string statusFalse[] = {
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

bool Tests::testReadWriteFile() {
    sudoku->resetGrid(sudoku->grid);

    std::string table[9] = {
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
    setGridValues(table);

    sudoku->writeToFile(testFileName, sudoku->grid); // writing to file
    sudoku->readFile(testFileName, sudoku->grid); // reading from file

    for (int i = 0; i < sudoku->DIMENSIONS; ++i) {
        for (int j = 0; j < sudoku->DIMENSIONS; ++j) {
            int testVal = table[i][j] - '0'; // converting char to int

            int rwVal = sudoku->grid[i][j]; // value passed through file

            if (testVal != rwVal) { // checking if value got changed while working with file
                std::cout << "Test failed: Grid written to and read from file doesn't match!" << std::endl;
                return false;
            }
        }
    }

    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testBacktrack() {
    sudoku->resetGrid(sudoku->grid);

    // testing with puzzle with only one solution
    std::string uniqueSolutionSudoku1[] = {
        "200801000",
        "000000043",
        "500000000",
        "000070800",
        "000000100",
        "020030000",
        "600000075",
        "003400000",
        "000200600"
    };

    // only solution to puzzle
    std::string uniqueSolutionSudokuSolution1[] = {
        "237841569",
        "186795243",
        "594326718",
        "315674892",
        "469582137",
        "728139456",
        "642918375",
        "853467921",
        "971253684"
    };
    setGridValues(uniqueSolutionSudoku1);

    sudoku->backtrack(sudoku->grid, 0, 0);

    for (int i = 0; i < sudoku->DIMENSIONS; ++i) {
        for (int j = 0; j < sudoku->DIMENSIONS; ++j) {
            int testVal = uniqueSolutionSudokuSolution1[i][j] - '0'; // converting char to int
            
            int expected = sudoku->grid[i][j]; // checking if every number matc the only solution
            if (testVal != expected) {
                std::cout << "Test failed: Sudoku solution doesn't match!" << std::endl;
                return false;
            }
        }
    }

    // testing with puzzle with only one solution
    std::string uniqueSolutionSudoku2[] = {
        "050300007",
        "000005024",
        "098020600",
        "901003206",
        "030000010",
        "500200008",
        "405090380",
        "010070002",
        "000104070"
    };

    // only solution to puzzle
    std::string uniqueSolutionSudokuSolution2[] = {
        "254316897",
        "763985124",
        "198427653",
        "981753246",
        "632849715",
        "547261938",
        "475692381",
        "319578462",
        "826134579"
    };
    setGridValues(uniqueSolutionSudoku2);

    sudoku->backtrack(sudoku->grid, 0, 0);

    for (int i = 0; i < sudoku->DIMENSIONS; ++i) {
        for (int j = 0; j < sudoku->DIMENSIONS; ++j) {
            int testVal = uniqueSolutionSudokuSolution2[i][j] - '0'; // converting char to int

            int expected = sudoku->grid[i][j]; // checking if every number matc the only solution
            if (testVal != expected) {
                std::cout << "Test failed: Sudoku solution doesn't match!" << std::endl;
                return false;
            }
        }
    }

    std::cout << "Test passed!" << std::endl;
    return true;
}

bool Tests::testGenerateSudoku() {
    sudoku->resetGrid(sudoku->grid);

    if (!testBacktrack() || !testMeanCellFillingFactor() || !testRandom()){
        std::cout << "Test failed: Dependent function test failed!" << std::endl;
        return false;
    }

    const int numIterations = 50;
    for (int i = 0; i < numIterations; ++i) {
        int removeCount = sudoku->LEVELHARD;
        sudoku->generateSudoku(sudoku->grid, removeCount);

        int actualyRemoved = 0;
        for (int j = 0; j < sudoku->DIMENSIONS; ++j) {
            for (int k = 0; k < sudoku->DIMENSIONS; ++k) {
                if (sudoku->grid[j][k] == sudoku->EMPTYCELLINT) {
                    actualyRemoved++;
                }
            }
        }

        if (!sudoku->backtrack(sudoku->grid, 0, 0)) {
            std::cout << "Test failed: Generated puzzle is unsolvable!" << std::endl;
            return false;
        }

        if (actualyRemoved != removeCount) {
            std::cout << "Test failed: Wrong amount of numbers removed!" << std::endl;
            return false;
        }

    }

    std::cout << "Test passed!" << std::endl;
    return true;
}


