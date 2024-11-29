/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 
*   06.2024
*
* 	class cube member functions
*/
#include "cube.h"

cube::cube()
{

} 

//constructor (order of sides is irrelevant)
//it is important each side is complete
cube::cube(int input_array[54])
{
	for(int i=4; i<50; i+=9)
	{
		switch (input_array[i])
		{
			case red:
					for(int l=0; l<3; l++)
					{
						for(int k=0; k<3; k++)
						{
							front.val[l][k] = input_array[(i-4)+k+(l*3)];
						}
					}
				break;
			case orange:
					for(int l=0; l<3; l++)
					{
						for(int k=0; k<3; k++)
						{
							back.val[l][k] = input_array[(i-4)+k+(l*3)];
						}
					}
				break;
			case blue:
					for(int l=0; l<3; l++)
					{
						for(int k=0; k<3; k++)
						{
							left.val[l][k] = input_array[(i-4)+k+(l*3)];
						}
					}
				break;
			case green:
					for(int l=0; l<3; l++)
					{
						for(int k=0; k<3; k++)
						{
							right.val[l][k] = input_array[(i-4)+k+(l*3)];
						}
					}
				break;
			case yellow:
					for(int l=0; l<3; l++)
					{
						for(int k=0; k<3; k++)
						{
							up.val[l][k] = input_array[(i-4)+k+(l*3)];
						}
					}
				break;
			case white:
					for(int l=0; l<3; l++)
					{
						for(int k=0; k<3; k++)
						{
							down.val[l][k] = input_array[(i-4)+k+(l*3)];
						}
					}
				break;
			default:
				break;
		}
	}
}

//printf function for one side
void cube::print_side(color s)
{
	switch (s)
	{
		case red:
			printf("red:\n");
			print_side_help(front);
			break;

		case orange:
			printf("orange:\n");
			print_side_help(back);
			break;
	
		case blue:
			printf("blue:\n");
			print_side_help(left);
			break;

		case green:
			printf("green:\n");
			print_side_help(right);
			break;

		case yellow:
			printf("yellow:\n");
			print_side_help(up);
			break;

		case white:
			printf("white:\n");
			print_side_help(down);
			break;

		default: 
				print_side(white);
				print_side(yellow);
				print_side(red);
				print_side(green);
				print_side(orange);
				print_side(blue);
			break;
	}
}

//help function for print
void cube::print_side_help(side s)
{
	for(int l=0; l<3; l++)
	{
		for(int k=0; k<3; k++)
		{
			printf("%d ",s.val[l][k]);
		} 
		printf("\n");
	}
	printf("\n");
}

//checks if two sides are the same
bool cube::same_color(side *s, color c) 
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (c != s->val[i][j])
			return false;	
		}			
	}
	return true;
}

//checks if one side is fixed and returns this side
int cube::one_side_fixed ()
{
	if (this->same_color(&front, red))
	{
		return 3;
	}
	if (this->same_color(&left, blue))
	{
		return 6;
	}
	if (this->same_color(&right, green))
	{
		return 4;
	}	
	if (this->same_color(&back, orange))
	{
		return 5;
	}
	if (this->same_color(&up, yellow))
	{
		return 2;
	}
	if (this->same_color(&down, white))
	{
		return 1;
	}
	return 0;
}

//checks if all sides are fixed
bool cube::allSidesFixed() 
{
		return (
		this->same_color(&front, red)&& 
		this->same_color(&left, blue)&& 
		this->same_color(&right, green)&& 
		this->same_color(&back, orange)&& 
		this->same_color(&up, yellow)&& 
		this->same_color(&down, white)
		);
}

