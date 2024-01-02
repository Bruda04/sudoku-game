#include "Menu.h"
#include <iostream> 

void menuMain(Sudoku9& sudoku) {
	clearTerminal();
	displayWelcome();

	pauseDialog();

	while (true) {
		sudoku.incrementRoundCounter(); //start of the new round

		clearTerminal();
		int loadFrom = dialogLoadFrom(); // getting users choice for loading the puzzle
		clearTerminal();

		switch (loadFrom) {
		case OPTIONGENERATESUDOKU:
			sudoku.generateSudoku(sudoku.grid, sudoku.LEVELHARD); // generate puzzle
			sudoku.writeToFile(sudoku.getUnsolvedFilename(), sudoku.grid); // write puzzle to file
			sudoku.displayGrid(sudoku.grid); // display the puzzle

			std::cout << "Your sudoku is placed in " << sudoku.getUnsolvedFilename() << std::endl;
			pauseDialog();

			break;

		case OPTIONLOADSUDOKU:
			dialogContinue(sudoku.getUnsolvedFilename()); // whaiting for user to place puzzle in file

			sudoku.readFile(sudoku.getUnsolvedFilename(), sudoku.grid); // loading puzzle from file
			sudoku.displayGrid(sudoku.grid); // displaying loaded puzzle

			pauseDialog();
			break;
		}

		clearTerminal();
		int solver = dialogSolver(); // getting users choice for loading the solution
		clearTerminal();

		switch (solver) {
		case OPTIONLOADSOLUTION:
			dialogContinue(sudoku.getSolvedFilename());
			sudoku.readFile(sudoku.getSolvedFilename(), sudoku.grid); // loading solved puzzle from file

			clearTerminal();

			sudoku.displayGrid(sudoku.grid); // displaying loaded solution
			{
				int g = 0; // placed good
				int b = 0; // placed bad
				int c = sudoku.getRoundCounter(); // round number
				sudoku.getStatistics(sudoku.grid, g, b); // calculating the statistics of the solution
				displayStats(c, g, b); // displaying the statistics
			}

			pauseDialog();
			break;

		case OPTIONSOLVESUDOKU:
			sudoku.backtrack(sudoku.grid, 0, 0); // solving the puzzle
			sudoku.writeToFile(sudoku.getSolvedFilename(), sudoku.grid); // writting the solution to file
			sudoku.displayGrid(sudoku.grid); // displaying the solution

			std::cout << "Your sudoku is placed in " << sudoku.getSolvedFilename() << std::endl;
			pauseDialog();
			break;
		}


		clearTerminal();
		int rematch = dialogRestart(); // getting user input for rematch/exit
		clearTerminal();

		switch (rematch) {
		case OPTIONRESTART:
			continue;
			break;
		case OPTIONEXIT:
			clearTerminal();
			return;
		}


	}

}

void displayWelcome() {
	std::cout << WELCOMEMESSAGE << std::endl;
}

void displayStats(unsigned int roundCount, unsigned int placedGood, unsigned int placedBad) {
	std::cout << "Your statistics for this game:" << std::endl;


	std::cout << "Number of rigthly placed numbers: " << placedGood << std::endl;
	std::cout << "Number of badly placed numbers: " << placedBad << std::endl;
	std::cout << "This is your round number - " << roundCount << std::endl;
	std::cout << std::endl;


}

unsigned short dialogLoadFrom() {

	std::cout << "Whould you like to:" << std::endl;
	std::cout << OPTIONLOADSUDOKU << ". Load sudoku" << std::endl;
	std::cout << OPTIONGENERATESUDOKU << ". Generate new sudoku" << std::endl;

	while (true) {
		std::cout << PROMPTCHAR;

		unsigned short userInput;
		std::cin >> userInput;
		std::cin.ignore(); // clearing the /n from cin buffer

		if (userInput == OPTIONLOADSUDOKU or userInput == OPTIONGENERATESUDOKU) {
			return userInput;
		} else {
			std::cout << "You must enter a valid option!" << std::endl;
		}
	}

}

unsigned short dialogSolver() {
	std::cout << "Whould you like to:" << std::endl;
	std::cout << OPTIONLOADSOLUTION << ". Load solved sudoku" << std::endl;
	std::cout << OPTIONSOLVESUDOKU << ". Generate sudoku solution" << std::endl;

	while (true) {
		std::cout << PROMPTCHAR;

		unsigned short userInput;
		std::cin >> userInput;
		std::cin.ignore(); // clearing the /n from cin buffer 

		if (userInput == OPTIONLOADSOLUTION or userInput == OPTIONSOLVESUDOKU) {
			return userInput;
		} else {
			std::cout << "You must enter a valid option!" << std::endl;
		}
	}
}

unsigned short dialogRestart() {
	clearTerminal();

	std::cout << "Whould you like to:" << std::endl;
	std::cout << OPTIONRESTART << ". Restart" << std::endl;
	std::cout << OPTIONEXIT << ". Exit" << std::endl;

	while (true) {
		std::cout << PROMPTCHAR;

		unsigned short userInput;
		std::cin >> userInput;
		std::cin.ignore(); // clearing the /n from cin buffer

		if (userInput == OPTIONRESTART or userInput == OPTIONEXIT) {
			return userInput;
		} else {
			std::cout << "You must enter a valid option!" << std::endl;
		}
	}
}

void dialogContinue(std::string filename) {
	std::cout << "You must now edit " << filename << std::endl; // displaying which file needs to be edited
	std::cout << "When you have finished editing" << std::endl;
	pauseDialog();

}

void pauseDialog() {
	std::cout << std::endl << "Press ENTER to continue." << std::endl; // pausing the execution until ENTER pressed
	std::cin.get();
}

void clearTerminal() {
	for (int i = 0; i < 50; ++i) {
		std::cout << std::endl; // pushing the output of the terminal out of scope
	}
}
