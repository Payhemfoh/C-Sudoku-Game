#include <iostream>
#include <vector>
#include <algorithm>
#include "../header/Sudoku.h"

/*
function to perform demonstration of map generation
set random timer, generate and display a new fully filled sudoku map
*/
void demonstration();

/*
function to allow user to play cmd-based Sudoku
game playing mode, generate map, remove some slots, and ask user to fill-in the sudoku, check answer at the end of the game
*/
void gameplay();

int main(int argc, char** argv) {
	bool demo = false;
	
	if (demo) {
		demonstration();
	}
	else {
		gameplay();
	}
	
	return 0;
}


void demonstration() {
	srand(time(NULL));
	Sudoku completeMap;
	std::cout << "Loading new Sudoku, please wait..." << std::endl;
	bool solved = completeMap.generate_new_map();
	while (solved != true) {
		completeMap.clean_map();
		solved = completeMap.generate_new_map();
	}
	completeMap.print_map();
}

void gameplay() {
	srand(time(NULL));

	//create object for different views (use for answer checking)
	Sudoku player_view;
	Sudoku temp_view;
	Sudoku answer;
	bool game_continue = true;

	while(game_continue){
		//generate a new sudoku map in answer view
		std::cout << "Loading new Sudoku, please wait..." << std::endl;

		bool solved = answer.generate_new_map();
		while (solved != true) {
			answer.clean_map();
			solved = answer.generate_new_map();
		}

		//copy to player_view and remove some slots
		player_view.copy(&answer);
		player_view.remove_number_from_map();

		//copy player_view to temp view and user will interact with temp view
		temp_view.copy(&player_view);
		temp_view.print_map();

		game_continue = temp_view.play(&answer, &player_view);
	}
}