#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class Sudoku {
	const static int MAP_SIZE = 9;
	int** map;

public:
	/*
	Constructor of the object, used to create and initialize the sudoku map
	*/
	Sudoku();

	/*
	Deconstructor of the object, will automatically clean memory usage of the object
	*/
	~Sudoku();

	/*
	Method to display the map in 2D format
	*/
	void print_map();

	/*
	Method to clean and initialize the value in map
	*/
	void clean_map();

	/*
	Method to generate a new fully filled Sudoku map
	-Sudoku constraints will be checked when value assigned
	*/
	bool generate_new_map();

	/*
	Method to check if the map has any empty slot
	-used in generate map to ensure the map is fully filled
	*/
	bool check_empty_slot();

	/*
	Method to remove value from map to create empty slot
	-used to initialize a game, and allow user to play the Sudoku
	*/
	void remove_number_from_map();

	/*
	Input method to change the value in the map
	@param:
	int x - the column to assign
	int y - the row to assign
	int value - the value to assign to the slot
	@return:
	result if the value is assigned correctly, false will be returned when input value out of bound
	*/
	bool insert_value(int x, int y, int value);

	/*
	Method to perform deep copy of map information between Sudoku objects
	*/
	void copy(Sudoku* other);

	/*
	Method to allow user to play sudoku game
	@params:
	Sudoku* answer - the fully filled map, for answer checking
	Sudoku* setting - the map with empty slot, for checking to ensure player cannot change the values
	*/
	bool play(Sudoku* answer, Sudoku* setting);

	/*
	Method to check if user correctly fill-in all value
	@params:
	Sudoku* answer - the fully filled map
	*/
	bool check_answer(Sudoku* answer);
};