/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 
*   06.2024
*
* 	header for class cube and color enum
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#ifndef CUBE_H
#define CUBE_H

//enum for the six colors
enum color 
{
	white = 1,
   	yellow = 2,
	red = 3,
	green = 4,
	orange = 5,
	blue = 6,
	def = 9,
};

//class for one side of a cube (a bit overkill to be honest ..)
class side 
{
	public:
	int val[3][3];
};

//main class for the cube
class cube
{	
	public:
	side front;
	side back;
	side left;
	side right;
	side up;
	side down;

	int temp [3][3];
	int temp_row [3];

	cube();
	cube(int input_array[54]);

	void print_side(color);
	void print_side_help(side);

	void cpy_mainside(side *);
	void rotate_left(color);
	void rotate_right(color);

	void rotate_mainside_left(side *);
	void rotate_mainside_right(side *);

	bool same_color(side *, color);

	int one_side_fixed ();
	bool allSidesFixed();

	bool operator==(const cube& c) 
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (this->front.val[i][j] != c.front.val[i][j])
				{
					return false;
				}
				else if (this->left.val[i][j] != c.left.val[i][j])
				{
					return false;
				}
				else if (this->right.val[i][j] != c.right.val[i][j])
				{
					return false;
				}
				else if (this->back.val[i][j] != c.back.val[i][j])
				{
					return false;
				}
				else if (this->up.val[i][j] != c.up.val[i][j])
				{
					return false;
				}
				else if (this->down.val[i][j] != c.down.val[i][j])
				{
					return false;
				}
		return true;
	}
};

#endif
