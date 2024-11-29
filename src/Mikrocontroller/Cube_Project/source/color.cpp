/*
 * color.cpp
 *
 *  Created on: 08.10.2024
 *      Author: gerri
 */
#include "Cube_Project.h"
#include "Adafruit_TCS34725.h"

color_c detect_color(uint16_t red, uint16_t green, uint16_t blue, uint16_t clear)
{
	int32_t small = green - blue - red;
	if(blue > 1200)
	{
		return c_white;
	}

	if((small > 0))
	{
		return c_green;
	}

	if(red < 350)
	{
		return c_blue;
	}

	if(green > 1000)
	{
		return c_yellow;
	}

	if(green > 400)
	{
		return c_orange;
	}

	return c_red;
}

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
	return (uint8_t)detected_color;
}

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

