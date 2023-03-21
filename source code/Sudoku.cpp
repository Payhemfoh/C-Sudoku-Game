#include "../header/Sudoku.h"

Sudoku::Sudoku() {
	map = new int* [MAP_SIZE];
	for (int i = 0; i < MAP_SIZE; ++i) {
		map[i] = new int[MAP_SIZE];
	}
	clean_map();
}

Sudoku::~Sudoku() {
	for (int i = 0; i < MAP_SIZE; ++i) {
		delete[] map[i];
	}

	delete[] map;
}

void Sudoku::print_map() {
	for (int y = 0; y < MAP_SIZE; ++y) {
		for (int x = 0; x < MAP_SIZE; ++x) {
			if (x % 3 == 2) {
				std::cout << map[y][x] << " | ";
			}
			else {
				std::cout << map[y][x] << " ";
			}
		}
		if (y % 3 == 2) {
			std::cout << "\n-------------------------";
		}
		std::cout << std::endl;
	}
}

void Sudoku::clean_map() {
	for (int y = 0; y < MAP_SIZE; ++y) {
		for (int x = 0; x < MAP_SIZE; ++x) {
			map[y][x] = 0;
		}
	}
}

bool Sudoku::generate_new_map() {
	std::vector<int> possible_values;

	for (int i = 0; i < 81; ++i) {
		int row = i / MAP_SIZE;
		int column = i % MAP_SIZE;

		if (map[row][column] != 0)
			continue;

		for (int value = 0; value < MAP_SIZE; ++value) {
			std::vector<int> column_values;
			std::vector<int> row_values;
			std::vector<int> block_values;

			for (int i = 0; i < MAP_SIZE; ++i) {
				int inblock_row = i / 3;
				int inblock_column = i % 3;
				int row_block = (int)(row / 3);
				int column_block = (int)(column / 3);

				column_values.push_back(map[row][i]);
				row_values.push_back(map[i][column]);
				block_values.push_back(map[inblock_row + (row_block * 3)][inblock_column + (column_block * 3)]);
				possible_values.push_back(i + 1);
			}

			std::random_shuffle(possible_values.begin(), possible_values.end());

			for (int value : possible_values) {
				std::vector<int>::iterator col_found = std::find(column_values.begin(), column_values.end(), value);
				std::vector<int>::iterator row_found = std::find(row_values.begin(), row_values.end(), value);
				std::vector<int>::iterator block_found = std::find(block_values.begin(), block_values.end(), value);

				if (col_found != column_values.end() || row_found != row_values.end() || block_found != block_values.end())
					continue;

				map[row][column] = value;

				if (check_empty_slot()) {
					return true;
				}
				else {
					if (generate_new_map())
						return true;
				}
			}
		}

		return false;
	}
}


bool Sudoku::check_empty_slot() {
	for (int x = 0; x < MAP_SIZE; ++x) {
		for (int y = 0; y < MAP_SIZE; ++y) {
			if (map[x][y] == 0)
				return false;
		}
	}
	return true;
}

void Sudoku::remove_number_from_map() {
	int rand_difficulty = (rand() % 10 + 35);

	for (int i = 0; i < rand_difficulty; ++i) {
		int rand_value = rand() % 81;
		int rand_row = rand_value / 9;
		int rand_column = rand_value % 9;

		if (map[rand_row][rand_column] != 0) {
			map[rand_row][rand_column] = 0;
		}
		else {
			--i;
		}
	}
}

bool Sudoku::insert_value(int x, int y, int value) {
	if (x < 0 || x >= MAP_SIZE) {
		return false;
	}
	else if (y < 0 || y >= MAP_SIZE) {
		return false;
	}
	else if (value <= 0 || value > MAP_SIZE) {
		return false;
	}

	map[x][y] = value;
	return true;

}

void Sudoku::copy(Sudoku* other) {
	for (int x = 0; x < MAP_SIZE; ++x) {
		for (int y = 0; y < MAP_SIZE; ++y) {
			this->map[x][y] = other->map[x][y];
		}
	}
}

bool Sudoku::play(Sudoku* answer, Sudoku* setting) {
	int xCoord; 
	int yCoord;  
	int ansNumber;
	bool game_valid = true;

	while (game_valid) {
		try {

			std::cout << "Enter the x co-ord of the square you would like to answer (top to bottom is 1 - 9): ";
			std::cin >> xCoord;
			std::cout << "Select the y co-ord of the square you would like to answer (left to right is 1 - 9): ";
			std::cin >> yCoord;

			if ((1 > xCoord && xCoord > 9) || (1 > yCoord && yCoord > 9)) {
				throw(std::string("Invalid coords!"));
			}
			else if (setting->map[(xCoord - 1)][(yCoord - 1)] != 0) {
				throw(std::string("That number already has a number in it!"));
			}
			else {
				std::cout << "Enter the number you think it is: ";
				std::cin >> ansNumber;
				if (ansNumber > 9 || ansNumber < 1) {
					throw(std::string("The number must be between 1 and 9!"));
				}
				this->map[(xCoord - 1)][(yCoord - 1)] = ansNumber;
				print_map();

				if (check_empty_slot()) {
					if (check_answer(answer)) {
						std::cout << "Well done! You completed the Sudoku! Restarting the program" << std::endl;
					}
					else {
						std::cout << "Unfortuntely, you have made an error in the Sudoku! Reseting the Sudoku..." << std::endl;
					}
					return true;
				}
			}
		}
		catch (std::string msg) {
			std::cerr << msg << std::endl;
		}
	}

	return false;
}

bool Sudoku::check_answer(Sudoku* answer) {
	for (int x = 0; x < MAP_SIZE; ++x) {
		for (int y = 0; y < MAP_SIZE; ++y) {
			if (this->map[x][y] != answer->map[x][y])
				return false;
		}
	}
	return true;
}