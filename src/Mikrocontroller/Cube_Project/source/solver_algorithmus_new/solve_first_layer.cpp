/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 06.2024
*   github.com/snech99
*
* 	solving the first layer
*/
#include "game.h"
#include "cube.h"
#include  <time.h>

void Game::solve_first_layer ()
{
	solve_first_layer_cross();
	solve_first_layer_all();
}	

void Game::solve_first_layer_cross()
{
	first_white_stone();
	while(check_white_cross() == 0)
	{
		find_white_edge_up();
		find_white_edge_down();
		middle_white_edge_up();
		down_white_edge_up();
	}

	if(check_white_cross() == 1)
	{
		move_Gamecube(3);
		move_Gamecube(3);
		move_Gamecube(4);
		move_Gamecube(4);
		move_Gamecube(5);
		move_Gamecube(5);
		move_Gamecube(6);
		move_Gamecube(6);

		find_white_edge_up();
	}
}

void Game::solve_first_layer_all()
{
	bool hit_flag = true;
	color side = red;
	bool all_done_flag = false;

	while(!all_done_flag)
	{
		while(hit_flag)
		{	
			white_corner_front_right(); 			
			hit_flag = white_corner_top();
		}
		hit_flag = true;


		all_done_flag = true;

		for(int i=0; i<4; i++)
		{
			if(!check_stone(next_side_circle(side),7))
			{
				get_down_corner_right(side);
				all_done_flag = false;
			}
			else
			{
				if(!check_stone(side,9))
				{
					get_down_corner_right(side);
					all_done_flag = false;
				}
			}
			side = next_side_circle(side);
		}	
	}	
}

void Game::white_corner_front_right()
{
	color side = red;
	color other_side = red;
	bool hit_flag = true;
	int count = 0;

	while(hit_flag)
	{
		if(get_color(side,3) == white)
		{
			other_side = get_color(next_side_circle(side), 1);
			while(other_side != next_side_circle(side))
			{
				side = next_side_circle(side);
				move_Gamecube(8);
			}
			count = 0;
			get_down_corner_front(side);
		}
		else
		{	
			count++;
			side = next_side_circle(side);
		}

		if(count > 4)
		{
			hit_flag = false;
		}
	}


	side = red;
	other_side = red;
	hit_flag = true;
	count = 0;

	while(hit_flag)
	{
		if(get_color(next_side_circle(side),1) == white)
		{
			other_side = get_color(side, 3);
			while(other_side != side)
			{
				side = next_side_circle(side);
				move_Gamecube(8);
			}
			count = 0;
			get_down_corner_right(side);
		}
		else
		{	
			count++;
			side = next_side_circle(side);
		}

		if(count > 4)
		{
			hit_flag = false;
		}
	}
}

bool Game::white_corner_top()
{
	color sec_color = red;
	color side = red;

	if(get_color(yellow,1) == white) 
	{
		sec_color = get_color(blue, 1);
		side = orange;

		while (sec_color != side)
		{	
			side = next_side_circle(side);
			move_Gamecube(8);
		}

		get_down_corner_front(side);
		get_down_corner_front(side);
		return true;
	}

	if(get_color(yellow,3) == white) 
	{
		sec_color = get_color(orange, 1);
		side = green;

		while (sec_color != side)
		{	
			side = next_side_circle(side);
			move_Gamecube(8);
		}

		get_down_corner_front(side);
		get_down_corner_front(side);
		return true;
	}

	if(get_color(yellow,7) == white) 
	{
		sec_color = get_color(red, 1);
		side = blue;

		while (sec_color != side)
		{	
			side = next_side_circle(side);
			move_Gamecube(8);
		}

		get_down_corner_front(side);
		get_down_corner_front(side);
		return true;
	}

	if(get_color(yellow,9) == white) 
	{
		sec_color = get_color(green, 1);
		side = red;

		while (sec_color != side)
		{	
			side = next_side_circle(side);
			move_Gamecube(8);
		}

		get_down_corner_front(side);
		get_down_corner_front(side);
		return true;
	}

	return false;
}

void Game::first_white_stone()
{
	int pos = 2;
	bool hit_flag = false;
	bool flag_check_color = false;

	while (pos <= 8)
	{
		if(check_stone(white,pos))
		{
			hit_flag = true;
			break;
		}
		pos += 2;
	}

	while (hit_flag)
	{
		if(hit_flag)
		{
			switch(pos)
			{
				case 2: flag_check_color = check_stone(red,8);
						break;
				case 4: flag_check_color = check_stone(blue,8);
						break;
				case 6: flag_check_color = check_stone(green,8);
						break;
				case 8: flag_check_color = check_stone(orange,8);
						break;
			}
		}

		if(!flag_check_color)
		{
			move_Gamecube(1);
			pos = next_pos(pos);
		}
		else
		{
			hit_flag = false;
		}
	}
}

void Game::find_white_edge_up()
{
	int pos = 2;
	bool hit_flag = false;
	bool flag_check_color = false;
	
	while(check_yellow_cross(white))
	{
		pos = 2;
		hit_flag = false;
		flag_check_color = false;

		while(!hit_flag)
		{
			if(get_color(yellow,pos) == white)
			{
				hit_flag = true;
			}
			else
			{
				pos = next_pos(pos);
			}
		}

		while(!flag_check_color)
		{
			switch(pos)
			{
				case 2: flag_check_color = check_stone(orange,2);
						break;
				case 4: flag_check_color = check_stone(blue,2);
						break;
				case 6: flag_check_color = check_stone(green,2);
						break;
				case 8: flag_check_color = check_stone(red,2);
						break;
			}

			if(!flag_check_color)
			{
				move_Gamecube(2);
				pos = next_pos(pos);
			}
			else
			{
				switch(pos)
				{
					case 2:	move_Gamecube(5);
							move_Gamecube(5);
							break;
					case 4: move_Gamecube(6);
							move_Gamecube(6);
							break;
					case 6: move_Gamecube(4);
							move_Gamecube(4);
							break;
					case 8: move_Gamecube(3);
							move_Gamecube(3);
							break;
				}
			}
		}
	}
}

void Game::find_white_edge_down()
{
	color side = red;
	color sec_edge_color = red;
	int count = 0;

	while (count < 4)
	{
		if(get_color(side,2) == white)
		{
			switch(side)
			{
				case red: sec_edge_color = get_color(yellow, 8);
					break;

				case green: sec_edge_color = get_color(yellow, 6);
					break;

				case orange: sec_edge_color = get_color(yellow, 2);
					break;

				case blue: sec_edge_color = get_color(yellow, 4);
					break;
			}

			while(sec_edge_color != side)
			{
				move_Gamecube(8);
				side = next_side_circle(side);
			}

			move_white_edge_down(side);
		}
		else
		{
			count++;
			side = next_side_circle(side);
		}
	}
}

void Game::middle_white_edge_up()
{
	color side = red;
	int count = 0;
	bool hit_flag = true;

	while(hit_flag && (count < 4))
	{
		if(get_color(side, 4) == white)
		{
			hit_flag = false;
			white_edge_up_left(side);
		}

		if(get_color(side, 6) == white)
		{
			hit_flag = false;
			white_edge_up_right(side);
		}

		side = next_side_circle(side);
		count++;
	}
}

void Game::down_white_edge_up()
{
	color side = red;
	int count = 0;
	bool hit_flag = true;

	while(hit_flag && (count < 4))
	{
		if(get_color(side, 8) == white)
		{
			hit_flag = false;
			switch(side)
			{
				case red:	move_Gamecube(3);
							move_Gamecube(3);
							break;

				case green: move_Gamecube(4);
							move_Gamecube(4);
							break;

				case orange:move_Gamecube(5);
							move_Gamecube(5);
							break;

				case blue: 	move_Gamecube(6);
							move_Gamecube(6);
							break;
			}
		}

		side = next_side_circle(side);
		count++;
	}
}

int Game::next_pos(int pos)
{
	switch(pos)
	{
		case 2: pos = 6;
			break;
		case 4: pos = 2;
			break;
		case 6: pos = 8;
			break;
		case 8: pos = 4;
			break;
	}
	return pos;
}

//help function for next side in the circle
color Game::next_side_circle (color col)
{
	int temp = (int) col;
	temp++;
	if(temp > 6)
	{
		temp = 3;
	}
	return ((color) temp);
}

//function to switch stones in the first layer
void Game::get_down_corner_front (color col)
{
	switch (col)
	{
		case red:	move_Gamecube(2);  	
					move_Gamecube(4);	
					move_Gamecube(8);	
					move_Gamecube(10);	
			break;

		case blue:	move_Gamecube(2);
					move_Gamecube(3);
					move_Gamecube(8);
					move_Gamecube(9);
			break;

		case green:	move_Gamecube(2);
					move_Gamecube(5);
					move_Gamecube(8);
					move_Gamecube(11);
			break;

		case orange:move_Gamecube(2);
					move_Gamecube(6);
					move_Gamecube(8);
					move_Gamecube(12);
			break;

		default: break;			
	}
}

//function to switch stones in the first layer
void Game::get_down_corner_right (color col)
{
	switch (col)
	{
		case red:	move_Gamecube(4);  	
					move_Gamecube(2);	
					move_Gamecube(10);	
			break;

		case blue:	move_Gamecube(3);
					move_Gamecube(2);
					move_Gamecube(9);
			break;

		case green:	move_Gamecube(5);
					move_Gamecube(2);
					move_Gamecube(11);
			break;

		case orange:move_Gamecube(6);
					move_Gamecube(2);
					move_Gamecube(12);
			break;

		default: break;			
	}
}

void Game::move_white_edge_down(color col)
{
	switch (col)
	{
		case red:	move_Gamecube(8); 	
					move_Gamecube(10);
					move_Gamecube(3);
					move_Gamecube(4);
			break;

		case blue:	move_Gamecube(8);
					move_Gamecube(9);
					move_Gamecube(6);
					move_Gamecube(3);
			break;

		case green:	move_Gamecube(8);
					move_Gamecube(11);
					move_Gamecube(4);
					move_Gamecube(5);
			break;

		case orange:move_Gamecube(8);
					move_Gamecube(12);
					move_Gamecube(5);
					move_Gamecube(6);
			break;

		default: break;			
	}
}

void Game::white_edge_up_right(color col)
{
	switch (col)
	{
		case red:	move_Gamecube(4); 	
					move_Gamecube(2);	
					move_Gamecube(10);	
			break;

		case blue:	move_Gamecube(3);
					move_Gamecube(2);
					move_Gamecube(9);
			break;

		case green:	move_Gamecube(5);
					move_Gamecube(2);
					move_Gamecube(11);
			break;

		case orange:move_Gamecube(6);
					move_Gamecube(2);
					move_Gamecube(12);
			break;

		default: break;			
	}
}

void Game::white_edge_up_left(color col)
{
	switch (col)
	{
		case red:	move_Gamecube(12); 	
					move_Gamecube(8);	
					move_Gamecube(6);	
			break;

		case blue:	move_Gamecube(11);
					move_Gamecube(8);
					move_Gamecube(5);
			break;

		case green:	move_Gamecube(9);
					move_Gamecube(8);
					move_Gamecube(3);
			break;

		case orange:move_Gamecube(10);
					move_Gamecube(8);
					move_Gamecube(4);
			break;

		default: break;			
	}
}

//get the color of a stone based on the side and position
color Game::get_color(color rainbow, int pos)
{
	int col = 0;
	int row = 0;

	convert_pos(&row, &col, pos);

	switch(rainbow)
	{
		case white: return ((color)c.down.val[row][col]);
			break;

		case red:	return ((color)c.front.val[row][col]);
			break;

		case yellow:return ((color)c.up.val[row][col]);
			break;

		case blue: 	return ((color)c.left.val[row][col]);
			break;

		case green: return ((color)c.right.val[row][col]);
			break;

		case orange:return ((color)c.back.val[row][col]);
			break;

		default:		return def;
			break;
	}
}

//checks if a stone is matching with the mid-stone
bool Game::check_stone (color rainbow, int pos)
{
	int row;
	int col;

	convert_pos(&row, &col, pos);

	switch (rainbow)
	{
		case white: if (c.down.val[row][col] == white)
					{
						return true;
					}
					return false;
					break;	

		case red: 	if (c.front.val[row][col] == red)
					{
						return true;
					}
					return false;
					break;

		case blue: 	if (c.left.val[row][col] == blue)
					{
						return true;
					}
					return false;
					break;

		case green: if (c.right.val[row][col] == green)
					{
						return true;
					}
					return false;
					break;

		case orange:if (c.back.val[row][col] == orange)
					{
						return true;
					}
					return false;
					break;
		case yellow:if (c.up.val[row][col] == yellow)
					{
						return true;
					}
					return false;
					break;
		default: return false;
				break;
	}
}

//gets the row and col based on a position
void Game::convert_pos (int *row, int *col, int pos)
{
	switch	(pos)
	{
		case 1:		*row = 0;
					*col = 0;
			break;
		case 2:		*row = 0;
					*col = 1;
			break;
		case 3:		*row = 0;
					*col = 2;
			break;
		case 4:		*row = 1;
					*col = 0;
			break;
		case 6:		*row = 1;
					*col = 2;
			break;
		case 7:		*row = 2;
					*col = 0;
			break;
		case 8:		*row = 2;
					*col = 1;
			break;
		case 9:		*row = 2;
					*col = 2;
			break;
		default:
			break;
	}
}

//checks for a yellow or white cross
bool Game::check_yellow_cross(color col)
{
	switch (col)
	{
		case yellow: 	if( (c.up.val[0][1] == yellow) && (c.up.val[1][0] == yellow) 
							&& (c.up.val[1][2] == yellow) && (c.up.val[2][1] == yellow))
						{
							return true;
						}
						return false;
						break;

		case white:		if( (c.up.val[0][1] == white) || (c.up.val[1][0] == white) 
							|| (c.up.val[1][2] == white) || (c.up.val[2][1] == white))
						{
							return true;
						}
						return false;
						break;
		default:		return false;
						break;
	}
}

int Game::check_white_cross()
{
	color side = red;
	bool hit_flag = true;

	if( !((c.down.val[0][1] == white) && (c.down.val[1][0] == white) 
		&& (c.down.val[1][2] == white) && (c.down.val[2][1] == white)) )
	{
		return 0;
	}

	for(int i=0; i<4; i++)
	{
		if(!check_stone(side,8))
		{
			hit_flag = false;
		}
		side = next_side_circle(side);
	}

	if(hit_flag)
	{
		return 2;
	}
	else
	{
		return 1;
	}
	
	return 0;
}
