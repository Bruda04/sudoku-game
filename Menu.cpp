#include "Menu.h"
#include <iostream> 

void menuMain(Sudoku9& sudoku) {
	clearTerminal();
	displayWelcome();

	pauseDialog();

	while (true) {
		sudoku.incrementRoundCounter();

		clearTerminal();
		int loadFrom = dialogLoadFrom();
		clearTerminal();

		switch (loadFrom) {
		case OPTIONGENERATESUDOKU:
			sudoku.generateSudoku(sudoku.grid, sudoku.LEVELHARD);
			sudoku.writeToFile(sudoku.getUnsolvedFilename(), sudoku.grid);
			std::cout << "Your sudoku is placed in " << sudoku.getUnsolvedFilename() << std::endl;
			pauseDialog();
			break;
		case OPTIONLOADSUDOKU:
			dialogContinue(sudoku.getUnsolvedFilename());
			sudoku.readFile(sudoku.getUnsolvedFilename(), sudoku.grid);
			break;
		}

		clearTerminal();
		int solver = dialogSolver();
		clearTerminal();

		switch (solver) {
		case OPTIONLOADSOLUTION:
			dialogContinue(sudoku.getSolvedFilename());
			sudoku.readFile(sudoku.getSolvedFilename(), sudoku.grid);

			clearTerminal();

			{
				int g = 0;
				int b = 0;
				int c = sudoku.getRoundCounter();
				sudoku.getStatistics(g, b);
				displayStats(c, g, b);
			}

			pauseDialog();
			break;
		case OPTIONSOLVESUDOKU:
			sudoku.backtrack(sudoku.grid, 0, 0);
			sudoku.writeToFile(sudoku.getSolvedFilename(), sudoku.grid);
			std::cout << "Your sudoku is placed in " << sudoku.getSolvedFilename() << std::endl;
			pauseDialog();
			break;
		}


		clearTerminal();
		int rematch = dialogRestart();
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
		std::cin.ignore();
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
		std::cin.ignore();
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
		std::cin.ignore();
		if (userInput == OPTIONRESTART or userInput == OPTIONEXIT) {
			return userInput;
		} else {
			std::cout << "You must enter a valid option!" << std::endl;
		}
	}
}

void dialogContinue(std::string filename) {
	std::cout << "You must now edit " << filename << std::endl;
	std::cout << "When you have finished editing, pleas press ENTER" << std::endl;
	pauseDialog();

}

void pauseDialog() {
	std::cout << std::endl << "Press ENTER to continue." << std::endl;
	std::cin.get();
}

void clearTerminal() {
	for (int i = 0; i < 50; ++i) {
		std::cout << std::endl;
	}
}
