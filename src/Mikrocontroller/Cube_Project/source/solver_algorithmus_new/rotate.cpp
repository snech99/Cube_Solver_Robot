/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 
*   06.2024
*
* 	rotate functions for the cube
*/
#include "cube.h"

//complete rotation left
void cube::rotate_left(color s)
{
	switch (s)
	{
		case red:	cpy_mainside(&front);
					rotate_mainside_left(&front);

					//rotation of the adjacent stones			
					for (int i=0; i<3; i++)
					{
						temp_row[i] = left.val[2-i][2];
						left.val[2-i][2] = up.val[2][i];
						up.val[2][i] = right.val[i][0];
						right.val[i][0] = down.val[0][2-i];
						down.val[0][2-i] = temp_row[i];
					}				
					break;

		case blue: 	cpy_mainside(&left);
					rotate_mainside_left(&left);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = back.val[2-i][2];
						back.val[2-i][2] = up.val[i][0];
						up.val[i][0] = front.val[i][0];
						front.val[i][0] = down.val[i][0];
						down.val[i][0] = temp_row[i];
					}					
					break;

		case green: cpy_mainside(&right);
					rotate_mainside_left(&right);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = front.val[2-i][2];
						front.val[2-i][2] = up.val[2-i][2];
						up.val[2-i][2] = back.val[i][0];
						back.val[i][0] = down.val[2-i][2];
						down.val[2-i][2] = temp_row[i];
					}			
					break;

		case orange:cpy_mainside(&back);
					rotate_mainside_left(&back);
				
					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = right.val[2-i][2];
						right.val[2-i][2] = up.val[0][2-i];
						up.val[0][2-i] = left.val[i][0];
						left.val[i][0] = down.val[2][i];
						down.val[2][i] = temp_row[i];
					}			
					break;

		case white: cpy_mainside(&down);
					rotate_mainside_left(&down);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = left.val[2][i];
						left.val[2][i] = front.val[2][i];
						front.val[2][i] = right.val[2][i];
						right.val[2][i] = back.val[2][i];
						back.val[2][i] = temp_row[i];
					}			 
					break;

		case yellow:cpy_mainside(&up);
					rotate_mainside_left(&up);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = left.val[0][2-i];
						left.val[0][2-i] = back.val[0][2-i];
						back.val[0][2-i] = right.val[0][2-i];
						right.val[0][2-i] = front.val[0][2-i];
						front.val[0][2-i] = temp_row[i];
					}			 
					break;
		default:
					break;
	}
}

//complete rotation left
void cube::rotate_right(color s)
{
	switch (s)
	{
		case red:	cpy_mainside(&front);
					rotate_mainside_right(&front);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = right.val[2-i][0];
						right.val[2-i][0] = up.val[2][2-i];
						up.val[2][2-i] = left.val[i][2];
						left.val[i][2] = down.val[0][i];
						down.val[0][i] = temp_row[i];
					}
					break;

		case blue: 	cpy_mainside(&left);
					rotate_mainside_right(&left);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = front.val[2-i][0];
						front.val[2-i][0] = up.val[2-i][0];
						up.val[2-i][0] = back.val[i][2];
						back.val[i][2] = down.val[2-i][0];
						down.val[2-i][0] = temp_row[i];
					}			
					break;

		case green: cpy_mainside(&right);
					rotate_mainside_right(&right);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = back.val[2-i][0];
						back.val[2-i][0] = up.val[i][2];
						up.val[i][2] = front.val[i][2];
						front.val[i][2] = down.val[i][2];
						down.val[i][2] = temp_row[i];
					}			
					break;

		case orange: cpy_mainside(&back);
					rotate_mainside_right(&back);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = left.val[2-i][0];
						left.val[2-i][0] = up.val[0][i];
						up.val[0][i] = right.val[i][2];
						right.val[i][2] = down.val[2][2-i];
						down.val[2][2-i] = temp_row[i];
					}			
					break;

		case white: cpy_mainside(&down);
					rotate_mainside_right(&down);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = right.val[2][2-i];
						right.val[2][2-i] = front.val[2][2-i];
						front.val[2][2-i] = left.val[2][2-i];
						left.val[2][2-i] = back.val[2][2-i];
						back.val[2][2-i] = temp_row[i];
					}			
					break;

		case yellow:cpy_mainside(&up);
					rotate_mainside_right(&up);

					//rotation of the adjacent stones					
					for (int i=0; i<3; i++)
					{
						temp_row[i] = right.val[0][i];
						right.val[0][i] = back.val[0][i];
						back.val[0][i] = left.val[0][i];
						left.val[0][i] = front.val[0][i];
						front.val[0][i] = temp_row[i];
					}			
					break;
		default:
				break;
	}
}

//copy of the main side
void cube::cpy_mainside(side *s)
{
	for (int i=0; i<3; i++)
	{ 
		for (int k=0; k<3; k++)
		{
			this->temp[i][k] = s->val[i][k];
		}
	}	
}

//rotation of the mainside right
void cube::rotate_mainside_right(side *s)
{
	int n =3;
	for (int i=0; i<3; i++)
	{
		for (int k=0; k<3; k++)
		{
			s->val[i][k] = this->temp[2-k][i];
		}
	}
}

//rotation of the mainside left
void cube::rotate_mainside_left(side *s)
{
	int n =3;
	for (int i=0; i<3; i++)
	{
		for (int k=0; k<3; k++)
		{
			s->val[i][k] = this->temp[k][2-i];
		}
	}
}
