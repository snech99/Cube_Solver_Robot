/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 
*   06.2024
*
* 	solving the second layer
*/
#include "game.h"
#include "cube.h"

//main solving algorithm
void Game::solve_second_layer()
{
    color mid = red;
    color stone_top = red;
    int count = 0;

    while (count < 4)
    {
        if(get_color(mid, 2) == yellow)
        {
            mid = next_side_circle(mid);
            count++;
        }  
        else
        {
            if( (stone_top = color_stone_top(mid)) == yellow ) 
            {
                mid = next_side_circle(mid);
                count++;
            }
            else
            {
                while(!check_stone(mid, 2))
                {
                    mid = next_side_circle(mid);
                    move_Gamecube(8);
                }
                if(stone_top == next_side_circle(mid))
                {
                    automove_right(mid);
                    count = 0;
                }
                else
                {
                    automove_left(mid);
                    count = 0;
                }
            }
        }
    }

	for (int i=3; i<7; i++)
	{
		mid = (color) i;
		if( !check_stone(mid, 6) || !check_stone(next_side_circle(mid), 4))
		{
			automove_right(mid);
			solve_second_layer();
		}
	}
}

//checks for a specific stone
color Game::color_stone_top(color col)
{
    switch (col)
    {
        case red:       return(get_color(yellow, 8));
                        break;

         case green:    return(get_color(yellow, 6));
                        break;

         case blue:     return(get_color(yellow, 4));
                        break;

         case orange:   return(get_color(yellow, 2));
                        break;

        default:        return (def);
                        break;
    }
}

//move to change a stone in the second layer
void Game::automove_left (color col)
{
    switch (col)
	{
		case red:	move_Gamecube(8);  	
					move_Gamecube(12);	
					move_Gamecube(2);	
					move_Gamecube(6);	
                    move_Gamecube(2);  	
					move_Gamecube(3);	
					move_Gamecube(8);	
					move_Gamecube(9);	
			break;

		case blue:	move_Gamecube(8);  	
					move_Gamecube(11);	
					move_Gamecube(2);	
					move_Gamecube(5);	
                    move_Gamecube(2);  	
					move_Gamecube(6);	
					move_Gamecube(8);	
					move_Gamecube(12);
			break;

		case green:	move_Gamecube(8);  	
					move_Gamecube(9);	
					move_Gamecube(2);	
					move_Gamecube(3);	
                    move_Gamecube(2);  	
					move_Gamecube(4);	
					move_Gamecube(8);	
					move_Gamecube(10);	
			break;

		case orange:move_Gamecube(8);  	
					move_Gamecube(10);
					move_Gamecube(2);	
					move_Gamecube(4);	
                    move_Gamecube(2);  	
					move_Gamecube(5);	
					move_Gamecube(8);
					move_Gamecube(11);
			break;

		default: break;			
	}
}

//move to change a stone in the second layer
void Game::automove_right (color col)
{
    switch (col)
	{
		case red:	move_Gamecube(2);  	
					move_Gamecube(4);	
					move_Gamecube(8);	
					move_Gamecube(10);	
                    move_Gamecube(8);  	
					move_Gamecube(9);	
					move_Gamecube(2);	
					move_Gamecube(3);	
			break;

		case blue:	move_Gamecube(2);  	
					move_Gamecube(3);	
					move_Gamecube(8);	
					move_Gamecube(9);	
                    move_Gamecube(8);  	
					move_Gamecube(12);	
					move_Gamecube(2);	
					move_Gamecube(6);	
			break;

		case green:	move_Gamecube(2);  
					move_Gamecube(5);	
					move_Gamecube(8);	
					move_Gamecube(11);	
                    move_Gamecube(8);  	
					move_Gamecube(10);	
					move_Gamecube(2);	
					move_Gamecube(4);	
			break;

		case orange:move_Gamecube(2);  	
					move_Gamecube(6);	
					move_Gamecube(8);	
					move_Gamecube(12);	
                    move_Gamecube(8);  	
					move_Gamecube(11);	
					move_Gamecube(2);	
					move_Gamecube(5);
			break;

		default: break;			
	}
}

