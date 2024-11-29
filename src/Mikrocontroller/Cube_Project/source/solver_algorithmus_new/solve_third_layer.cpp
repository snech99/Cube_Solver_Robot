/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 
*   06.2024
*
* 	solving the third and last layer
*/
#include "game.h"
#include "cube.h"

//main solving function
void Game::solve_third_layer()
{
    while(!check_yellow_cross(yellow))
    {
        switch (read_yellow_cross())
        {
            case 5:     move_Gamecube(8);    
                        break;
            case 12:    move_Gamecube(8); 
                        move_Gamecube(8);   
                        break;
            case 10:    move_Gamecube(2); 
                        break;
            case 9:     move_Gamecube(8);   
                        break;
        }
        KREUZZUG();
    }

    while( !c.same_color(&(c.up), yellow) )
    {
        switch (read_yellow_x())
        {
            case 1:     if (get_color(blue, 3) == yellow)
                        {
                            move_Gamecube(8); 
                            fisch_right();
                        }
                        else
                        {
                            move_Gamecube(8);
                            move_Gamecube(8);
                            fisch_left();
                        }   
                        break;

            case 4:     if (get_color(red, 3) == yellow)
                        {
                            fisch_right();
                        }
                        else
                        {
                            move_Gamecube(8);
                            fisch_left();
                        }   
                        break;

            case 8:     if (get_color(green, 3) == yellow)
                        {
                            move_Gamecube(2);
                            fisch_right();
                        }
                        else
                        {
                            fisch_left();
                        }  
                        break;

            case 2:     if (get_color(orange, 3) == yellow)
                        {
                            move_Gamecube(2);
                            move_Gamecube(2);
                            fisch_right();
                        }
                        else
                        {
                            move_Gamecube(2);
                            fisch_left();
                        } 
                        break;


            case 12:    if (get_color(orange, 3) == yellow)
                        {
                            move_Gamecube(2);
                            move_Gamecube(2);
                            fisch_right();
                        }
                        else
                        {
                            move_Gamecube(8);
                            fisch_right();
                        } 
                        break;

            case 10:    if (get_color(blue, 3) == yellow)
                        {
                            move_Gamecube(8);
                            fisch_right();
                        }
                        else
                        {
                            fisch_right();
                        } 
                        break;

            case 3:     if (get_color(red, 3) == yellow)
                        {
                            fisch_right();
                        }
                        else
                        {
                            move_Gamecube(2);
                            fisch_right();
                        } 
                        break;

            case 5:     if (get_color(green, 3) == yellow)
                        {
                            move_Gamecube(2);
                            fisch_right();
                        }
                        else
                        {
                            move_Gamecube(2);
                            move_Gamecube(2);
                            fisch_right();
                        } 
                        break;

            case 0:     align_yellow_cross();
                        fisch_right();
                        break;

            case 6:     if (get_color(orange, 3) == yellow)
                        {
                            move_Gamecube(2);
                            fisch_right();
                        }
                        else
                        {
                            move_Gamecube(8);
                            fisch_right();
                        } 
                        break;

            case 9:     if (get_color(green, 3) == yellow)
                        {
                            fisch_right();
                        }
                        else
                        {
                            move_Gamecube(2);
                            move_Gamecube(2);
                            fisch_right();
                        } 
                        break;
        }
    }
       
    align_rainbow_middle();
    finish_cube();
}

//move to change a stone in the third layer
void Game::KREUZZUG()
{
    move_Gamecube(3);  	
	move_Gamecube(4);	
	move_Gamecube(2);	
	move_Gamecube(10);
    move_Gamecube(8);  	
	move_Gamecube(9);		
}

//move to change a stone in the third layer
void Game::align_yellow_cross()
{
    color mid = red;
    int pos = 0;
    int erg = 0;
    for (int i=0; i<4; i++)
    {
        if (get_color(mid, 1) == yellow)
        {
            erg += pow(2, pos);
        }
        pos++;

        if (get_color(mid, 3) == yellow)
        {
            erg += pow(2, pos);
        }
        pos++;
        mid = next_side_circle(mid);
    }

    switch (erg)
    {
            case 210:   break;

            case 75:    move_Gamecube(2);
                        break;

            case 45:    move_Gamecube(2);
                        move_Gamecube(2);
                        break;

            case 180:   move_Gamecube(8);
                        break;

            case 204:   break;

            case 51:    move_Gamecube(8);
                        break;
    }
}

//reads out a special position
int Game::read_yellow_cross()
{
    int pos = 0;
    color col;
    int erg = 0;

    for (int i=2; i<9; i+=2)
    {
        col = get_color(yellow, i);
        if (col == yellow)
        {
            erg += pow(2, pos);
        }
        pos++;
    }   
    return erg;
}

//reads out a special position
int Game::read_yellow_x()
{
    int pos = 0;
    int num = 0;
    color col;
    int erg = 0;

    for (int i=0; i<4; i++)
    {
        switch(i)
        {
                case 0: num = 1;
                        break;
                case 1: num = 3;
                        break;
                case 2: num = 7;
                        break;
                case 3: num = 9;
                        break;
        }

        col = get_color(yellow, num);
        if (col == yellow)
        {
            erg += pow(2, pos);
        }
        pos++;
    }   
    return erg;
}

//move to change a stone in the third layer
void Game::fisch_left()
{
    move_Gamecube(12);  	
	move_Gamecube(8);	
	move_Gamecube(6);	
    move_Gamecube(8);	
	move_Gamecube(12);
    move_Gamecube(8);  	
	move_Gamecube(8);
    move_Gamecube(6);
}

//move to change a stone in the third layer
void Game::fisch_right()
{
    move_Gamecube(4);  	
	move_Gamecube(2);	
	move_Gamecube(10);	
    move_Gamecube(2);	
	move_Gamecube(4);
    move_Gamecube(2);  	
	move_Gamecube(2);
    move_Gamecube(10);
}

//move to change a stone in the third layer
void Game::rotate_Kantensteine(color mid)
{
    switch (mid)
    {
        case red:   move_Gamecube(10);  
	                move_Gamecube(2);	
	                move_Gamecube(10);	
                    move_Gamecube(8);	
	                move_Gamecube(10);  
                    move_Gamecube(8);  	
	                move_Gamecube(10);  
                    move_Gamecube(2);   
                    move_Gamecube(4);  	
	                move_Gamecube(2);	
	                move_Gamecube(10);	
                    move_Gamecube(10);  
                    break;

        case orange:move_Gamecube(12);  	
	                move_Gamecube(2);	
	                move_Gamecube(12);	
                    move_Gamecube(8);	
	                move_Gamecube(12);  
                    move_Gamecube(8);  	
	                move_Gamecube(12);  
                    move_Gamecube(2);   
                    move_Gamecube(6);  	
	                move_Gamecube(2);	
	                move_Gamecube(12);	
                    move_Gamecube(12);  
                    break;

        case green: move_Gamecube(11);  	
	                move_Gamecube(2);	
	                move_Gamecube(11);	
                    move_Gamecube(8);	
	                move_Gamecube(11);   
                    move_Gamecube(8);  	
	                move_Gamecube(11);  
                    move_Gamecube(2);   
                    move_Gamecube(5);  	
	                move_Gamecube(2);	
	                move_Gamecube(11);	
                    move_Gamecube(11);  
                    break;

        case blue:  move_Gamecube(9);  
	                move_Gamecube(2);	
	                move_Gamecube(9);	
                    move_Gamecube(8);	
	                move_Gamecube(9); 
                    move_Gamecube(8);  	
	                move_Gamecube(9);  
                    move_Gamecube(2);   
                    move_Gamecube(3);  	
	                move_Gamecube(2);	
	                move_Gamecube(9);	
                    move_Gamecube(9);  
                    break;

        default:    break;

    }

}

//move to change a stone in the third laye
void Game::L_move (color col)
{
    switch (col)
    {
        case red:   move_Gamecube(4);   
	                move_Gamecube(11);  
	                move_Gamecube(4);	
                    move_Gamecube(3);	
	                move_Gamecube(3);   
                    move_Gamecube(10);  
	                move_Gamecube(5);   
                    move_Gamecube(4);   
                    move_Gamecube(3);  	
	                move_Gamecube(3);	
	                move_Gamecube(4);	
                    move_Gamecube(4);	
                    break;

        case blue:  move_Gamecube(3);   
	                move_Gamecube(10);  
	                move_Gamecube(3);	
                    move_Gamecube(6);	
	                move_Gamecube(6);   
                    move_Gamecube(9);   
	                move_Gamecube(4);   
                    move_Gamecube(3);   
                    move_Gamecube(6);  	
	                move_Gamecube(6);	
	                move_Gamecube(3);	
                    move_Gamecube(3);
                    break;

        case orange:move_Gamecube(6);   
	                move_Gamecube(9);   
	                move_Gamecube(6);	
                    move_Gamecube(5);	
	                move_Gamecube(5);   
                    move_Gamecube(12);  
	                move_Gamecube(3);   
                    move_Gamecube(6);   
                    move_Gamecube(5);  
	                move_Gamecube(5);	
	                move_Gamecube(6);	
                    move_Gamecube(6);	
                    break;

        case green: move_Gamecube(5);   
	                move_Gamecube(12);  
	                move_Gamecube(5);	
                    move_Gamecube(4);	
	                move_Gamecube(4);   
                    move_Gamecube(11); 
	                move_Gamecube(6);  
                    move_Gamecube(5);   
                    move_Gamecube(4);  
	                move_Gamecube(4);	
	                move_Gamecube(5);	
                    move_Gamecube(5);
                    break;

    }
}

//move to change a stone in the third laye
void Game::align_rainbow_middle()
{
    int num = 0;
    color mid = red;
    color stone_front = get_color(red, 2);
    color stone_back  = get_color(orange, 2);

    switch (stone_back)
    {
        case blue:  stone_back = green; 
                    break;
        case green: stone_back = blue; 
                    break;
        case red:   stone_back = orange; 
                    break;
        case orange:stone_back = red; 
                    break;
    }

    if (stone_front == stone_back)
    {
        rotate_Kantensteine(red);
    }

    while (num != 1)
    {
        num = 0;
        for (int i=3; i<7; i++)
        {
            if(check_stone((color)i, 2))
            {
                num++;
                mid = (color) i;
            }
        }
        if (num > 1)
        {
            move_Gamecube(2);
        }
        else if (num == 1)
        {
            switch(mid)
            {
                case red:   if( (get_color(next_side_circle(mid), 2)) == orange )
                            {
                                 move_Gamecube(2);
                                 num = 3;
                            }
                            break;

                case green: if( (get_color(next_side_circle(mid), 2)) == blue )
                            {
                                 move_Gamecube(2);
                                 num = 3;
                            }
                            break;

                case blue:  if( (get_color(next_side_circle(mid), 2)) == green )
                            {
                                 move_Gamecube(2);
                                 num = 3;
                            }
                            break;

                case orange:if( (get_color(next_side_circle(mid), 2)) == red )
                            {
                                 move_Gamecube(2);
                                 num = 3;
                            }
                break;
            }
        }
        else
        {
            move_Gamecube(2);
            num = 3;
        }
    }
    rotate_Kantensteine(mid);
}  

//last algorithm until the cube is solved
void Game::finish_cube()
{
    color mid = red; 
    int check = 0;

    while(!this->c.allSidesFixed())
    { 
        for(int i=3; i<7; i++)
        {
            mid = (color) i;

            if(check_stone(mid, 3))
            {
                check = 1;
                switch(mid)
                {
                    case red:   L_move(orange);
                                break;
                    case green: L_move(blue);
                                break;
                    case orange:L_move(red);
                                break;
                    case blue:  L_move(green);
                                break;
                }
            }

            if (this->c.allSidesFixed())
            {
                return;
            }
        } 

        if (check == 0)
        {
            L_move(red);
        }
    }
}