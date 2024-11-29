/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 
*   06.2024
*
* 	class game member functions
*/
#include "game.h"
#include "cube.h"

using namespace std;

//set a cube to the game
void Game::setcube(cube *cu)
{
	del_cube_ptr = new cube (*cu);
	c = *del_cube_ptr;
}

void Game::del_cube()
{
	delete(del_cube_ptr);
}

//get the cube of a game
cube Game::get_cube()
{
	return this->c;
}

void Game::cleanup_moves()
{
	for (int i=0; i<200; i++)
	{
		move_array_all[i] = 0;
	}
	POS = 0;
}
	
//checks if one side is fixed
int Game::hasWon() 
{
	return c.one_side_fixed();
}

//print the cube of the game
void Game::print_cube()
{
	this->c.print_side(def);
}

//print the hole move array
void Game::print_move_array_all()
{
	for(int i=0; i<POS; i++)
	{
		printf("%d ", this->move_array_all[i]);
	}
	printf("   %d\n", POS);
}

//saves the moves into the big move_array_all
void Game::save_move(int move)
{
	move_array_all[POS] = move;
	POS++;

	if(POS >= 200)
	{
		printf("move_array_all is full!\n");
	}
}

//moves the cube of the game and saves them (only outside the DSF)
void Game::move_Gamecube(int move)
{
    switch (move)
    {
		case 1:	
				c.rotate_right(white);
				save_move(1);
			break;

		case 2: 
				c.rotate_right(yellow);
				save_move(2);
			break;

		case 3:
				c.rotate_right(red);
				save_move(3);
			break;

		case 4: 
				c.rotate_right(green);
				save_move(4);
			break;

		case 5:
				c.rotate_right(orange);
				save_move(5);
			break;

		case 6: 
				c.rotate_right(blue);
				save_move(6);
			break;

		case 7:	
				c.rotate_left(white);
				save_move(7);
			break;

		case 8: 
				c.rotate_left(yellow);
				save_move(8);
			break;

		case 9: 
				c.rotate_left(red);
				save_move(9);
			break;

		case 10:
				c.rotate_left(green);
				save_move(10);
			break;

		case 11: 
				c.rotate_left(orange);
				save_move(11);
			break;

		case 12: 
				c.rotate_left(blue);
				save_move(12);
			break; 
    }
}

//converts the move array back and writes the move_array of the DSF 
//and the one of the other algorithms together
void Game::complete_move_array (int* array)
{
	int pos = 0;

	for (int i=0; i<POS; i++)
	{
		array[pos] = move_array_all[i];
		pos++;			
	}
}

//looking for 3 moves in a row and deletes them -> replace with counter move
int Game::short_things_up_3(int *array_old, int *array_short)
{

	int count = 0;
	int new_move = 0;
	int old_move = 0;
	int move = 0;
	int pos = 0;
	int count_pos = 0;

	int pos_old = 0;
	int pos_new = 0;

	int saved = 0;

	for(int i=0; i<200; i++)
	{
		array_short[i] = 0;
	}

	while(array_old[count_pos] != 0)
	{
		new_move = array_old[count_pos];

		if (old_move == new_move)
		{
			count++;
		}
		else
		{
			count = 0;
		}

		if (count == 2)
		{	
			saved = saved + 2;
			if (array_old[count_pos] < 7)
			{
				move = array_old[count_pos]+6;
			}
			else
			{
				move = array_old[count_pos]-6;
			}
			pos = pos-2;
			array_short[pos] = move;
			old_move = move;
			pos++;
			count = 0;
		}
		else
		{
			array_short[pos] = array_old[count_pos];
			old_move = new_move;
			pos++;
		}	
		count_pos++;
	}
	
	return saved;
}

//searches for a move and a counter move successively -> deletes both
int Game::short_things_up_up_down(int *array_old, int *array_short)
{
	int new_move = 0;
	int old_move = 0;
	int move = 0;
	int pos = 0;
	int count_pos = 0;

	int saved = 0;

	for(int i=0; i<200; i++)
	{
		array_short[i] = 0;
	}

	while(array_old[count_pos] != 0)
	{
		array_short[pos] = array_old[count_pos];

		new_move = array_old[count_pos];

		if (new_move > 7)
		{
			move = new_move-6;
		}
		else
		{
			move = new_move+6;
		}

		if (move == old_move)
		{
			saved = saved + 2;
			pos = pos-2;
			old_move = array_short[pos];
		}
		else
		{
			old_move = new_move;
		}	
		pos++;
		count_pos++;
	}
	return saved;
}



			
