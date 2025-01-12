/*
*   Gerrit Hinrichs 01.2025
*   github.com/snech99
*
*   Cube_Solver_Robot
*   file to use the solver on the Microcontroller
*/


#include "cube.h"
#include "game.h"
#include "do_magic.h"

int move_array [200] = {};
int *ptr_array = move_array;
int move_array_short [200] = {};
int *ptr_array_short = move_array_short;
Game G;
Game G_Test;

int do_magic (int *input, int *output)
{
	for (uint8_t i=0; i<200; i++)
	{
		move_array[i] = 0;
	}

	int count = 0;
	cube C1(input);

	G.setcube(&C1);
	G.cleanup_moves();

	G_Test.setcube(&C1);
	G_Test.cleanup_moves();

	//solving the cube layer by layer
	G.solve_first_layer();
	G.solve_second_layer();
	G.solve_third_layer();

	//optimize the finale move_array
	G.complete_move_array(ptr_array);

	G.short_things_up_3(ptr_array, ptr_array_short);
	G.short_things_up_up_down(ptr_array_short, output);

	G.short_things_up_3(output, ptr_array_short);
	G.short_things_up_up_down(ptr_array_short, output);

	G.del_cube();

	//test the moves
	for(int i=0; i<200; i++)
	{
		if(output[i] != 0)
		{
			G_Test.move_Gamecube(output[i]);
			count++;
		}
	}
	
	//check for win
	if (G_Test.get_cube().allSidesFixed())
	{
		G_Test.del_cube();
		return count;
	}
	else
	{
		G_Test.del_cube();
		return -1;
	}
}
