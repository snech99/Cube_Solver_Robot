/*
*   Gerrit Hinrichs 01.2025
*   github.com/snech99
*
*   Cube_Solver_Robot
*   read and interpret the colors
*/

#include "Cube_Project.h"
#include "Adafruit_TCS34725.h"

// returns the color based on the RGB value
color_c detect_color(uint16_t red, uint16_t green, uint16_t blue, uint16_t clear)
{
	int sum = green + blue;
	if(red < 1500)
	{
		if(sum < 1500)
		{
			return c_red;
		}
		else
		{
			if(blue < 1000)
			{
				return c_green;
			}
			else
			{
				return c_blue;
			}
		}
	}

	if(green < 2000)
	{
		return c_orange;
	}

	if(blue > 2000)
	{
		return c_white;
	}

	return c_yellow;
}

// reading of the RGB value and returning the color
uint8_t get_color()
{
    uint16_t r_raw, g_raw, b_raw, c_raw;
    color_c detected_color;
	color_busy_flag = true;

	tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE);
	tcs.setInterrupt(true);

	tcs.getRawData(&r_raw, &g_raw, &b_raw, &c_raw);
	detected_color = detect_color(r_raw, g_raw, b_raw, c_raw);

	tcs.clearInterrupt();

	while(color_busy_flag)
	{

	}

	/*
	char buf_5[5] = {};
	char buf_6[5] = {};
	char buf_7[5] = {};
	char erg_c[2] = {};

	itoa(r_raw,buf_5,10);
	itoa(g_raw,buf_6,10);
	itoa(b_raw,buf_7,10);

	itoa((int)detected_color,erg_c,10);

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();

	ssd1309_SetCursor(3,3);
	ssd1309_WriteString(buf_5,Font_7x10, White);

	ssd1309_SetCursor(3,20);
	ssd1309_WriteString(buf_6,Font_7x10, White);

	ssd1309_SetCursor(3,37);
	ssd1309_WriteString(buf_7,Font_7x10, White);

	ssd1309_SetCursor(50,25);
	ssd1309_WriteString(erg_c,Font_7x10, White);

	ssd1309_UpdateScreen();
	*/
	return (uint8_t)detected_color;
}

// checks the scanned colors (counting)
bool check_colors()
{
	uint8_t count_white = 0;
	uint8_t count_yellow = 0;
	uint8_t count_red = 0;
	uint8_t count_green = 0;
	uint8_t count_orange = 0;
	uint8_t count_blue = 0;

	for(uint8_t i=0; i<54; i++)
	{
		switch(cube_array[i])
		{
			case 1:	count_white++;
					break;
			case 2: count_yellow++;
					break;
			case 3: count_red++;
					break;
			case 4:	count_green++;
					break;
			case 5:	count_orange++;
					break;
			case 6:	count_blue++;
					break;
		}
	}

	if(count_white > 9)
	{
		return false;
	}

	if(count_yellow > 9)
	{
		return false;
	}

	if(count_red > 9)
	{
		return false;
	}

	if(count_green > 9)
	{
		return false;
	}

	if(count_orange > 9)
	{
		return false;
	}

	if(count_blue > 9)
	{
		return false;
	}
	return true;
}

