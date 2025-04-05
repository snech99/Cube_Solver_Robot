/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 06.2024
*   github.com/snech99
*
* 	header for game class
*/
#include "cube.h"

using namespace std;

#ifndef	GAME_NEW_H
#define GAME_NEW_H

class Game 
{
	cube c;
	cube *del_cube_ptr;

	int move_array_all[200] = {};		//saves the moves of the other algorithms
	int POS = 0;
	
	public:
	//constructor
	Game()
	{

	}

	Game(cube *cu)
	{
		del_cube_ptr = new cube (*cu);
		c = *del_cube_ptr;
	}

	//destructor
	~Game()
	{
		delete(del_cube_ptr);
	}

	void setcube(cube *cu);
	cube get_cube();

	void cleanup_moves();
	void del_cube();

	int hasWon();
	void print_cube();

	void print_move_array_all();
	void save_move(int);
	void move_Gamecube(int);

	//main functions
	//void new_foo();	!!!
	void solve_first_layer();
	void solve_second_layer();
	void solve_third_layer();	

	//help functions for first layer

	void first_white_stone();
	void find_white_edge_up();
	void find_white_edge_down();
	void move_white_edge_down(color);
	void middle_white_edge_up();
	void white_edge_up_right(color);
	void white_edge_up_left(color);
	void down_white_edge_up();
	int next_pos(int);
	int check_white_cross();
	void solve_first_layer_cross();
	void solve_first_layer_all();
	void white_corner_front_right();
	bool white_corner_top();
	color next_side_circle (color);
	void get_down_corner_front(color);
	void get_down_corner_right(color);
	color get_color(color, int);
	bool check_stone (color, int);
	void convert_pos (int *, int *, int);
	bool check_yellow_cross(color);

	//help functions for second_layer
	void automove_left (color);
	void automove_right (color);
	color color_stone_top(color);

	//help functions for third_layer
	int read_yellow_cross();
	int read_yellow_x();
	void KREUZZUG();
	void fisch_left();
	void fisch_right();
	void align_yellow_cross();
	void rotate_Kantensteine(color );
	void L_move(color);
	void align_rainbow_middle();
	bool middle_rainbow_done();
	void finish_cube();

	int Test_cube_success(Game);
	void complete_move_array (int*);
	int short_things_up_3 (int *, int *);
	int short_things_up_up_down (int *, int *);
};

#endif
