#include "Menu.h"
#include "Sudoku9.h"
#include <iostream>

int main(int argc, char* argv[]) {
    /*if (argc != 3) {
        std::cerr << "Two arguments expected." << std::endl;
        return 1;
    }

    std::string firstFilename = argv[1];
    std::string secondFilename = argv[2];*/

    std::string firstFilename = "prvi.txt";
    std::string secondFilename = "drugi.txt";

    Sudoku9 sudoku(firstFilename, secondFilename);

    menuMain(sudoku);

    return 0;
}