// Author: Luka Bradic SV53/2022
// Last update: 1.1.2024.
// About:
// Main function for the Sudoku program

#include "Menu.h"
#include "Sudoku9.h"
#include "Tests.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Two arguments expected." << std::endl;
        return 1;
    }

    std::string firstFilename = argv[1];
    std::string secondFilename = argv[2];

    Sudoku9 sudoku(firstFilename, secondFilename);

    
    menuMain(sudoku); // comment if running tests
    
    
    Tests test(&sudoku);
    //test.testMain(); // uncomment to start tests

    return 0;
}