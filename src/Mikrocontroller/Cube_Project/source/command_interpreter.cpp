#include "Cube_Project.h"

bool check_blue(uint8_t*);
bool check_read_color(uint16_t*);
bool check_random(uint16_t*);
bool check_solve(uint16_t*);
bool check_send_cube (uint16_t *);
bool check_moves (uint16_t *);
bool check_change (uint16_t *);


message get_command_and_data (uint8_t *read_array)
{
	message msg;

    uint16_t string_pos_command = 0;
    uint16_t string_pos_data = 0;
    uint16_t string_pos_rx = 1;
    uint16_t command_string[32] = {};

    while(read_array[string_pos_rx] != '!')
    {
    	command_string[string_pos_command] = read_array[string_pos_rx];
    	string_pos_rx++;
        string_pos_command++;
    }


    while(read_array[string_pos_rx] != '%')
    {
    	if(read_array[string_pos_rx] == '!')
    	{
    		string_pos_rx++;
    	}
    	else
    	{
    		msg.m_data[string_pos_data] = read_array[string_pos_rx];
    		string_pos_rx++;
    		string_pos_data++;
    	}
    }

    msg.m_command = err;

    if (check_read_color(command_string))
    {
    	msg.m_command = read_color;
    	return msg;
    }

    if (check_random(command_string))
    {
    	msg.m_command = com_random;
    	return msg;
    }

    if (check_solve(command_string))
    {
    	msg.m_command = solve;
    	return msg;
    }

    if (check_send_cube(command_string))
    {
    	msg.m_command = send_cube;
    	return msg;
    }

    if (check_moves(command_string))
    {
       	msg.m_command = moves;
       	return msg;
    }

    if (check_change(command_string))
	{
		msg.m_command = change;
		return msg;
	}

    return msg;
}

bool check_read_color(uint16_t* array)
{
	uint8_t test_read[10] = {'r','e','a','d','_','c','o','l','o','r'};

	for (int i=0; i<10; i++)
	{
		if(test_read[i] != array[i])
		{
			return false;
		}
	}
	return true;
}

bool check_random(uint16_t* array)
{
	uint8_t test_read[6] = {'r','a','n','d','o','m'};

	for (int i=0; i<6; i++)
	{
		if(test_read[i] != array[i])
		{
			return false;
		}
	}
	return true;
}

bool check_solve(uint16_t* array)
{
	uint8_t test_read[5] = {'s','o','l','v','e'};

	for (int i=0; i<5; i++)
	{
		if(test_read[i] != array[i])
		{
			return false;
		}
	}
	return true;
}

bool check_send_cube(uint16_t* array)
{
	uint8_t test_read[9] = {'s','e','n','d','_','c','u','b','e'};

	for (int i=0; i<9; i++)
	{
		if(test_read[i] != array[i])
		{
			return false;
		}
	}
	return true;
}

bool check_moves(uint16_t* array)
{
	uint8_t test_read[5] = {'m','o','v','e','s'};

	for (int i=0; i<5; i++)
	{
		if(test_read[i] != array[i])
		{
			return false;
		}
	}
	return true;
}

bool check_change(uint16_t* array)
{
	uint8_t test_read[6] = {'c','h','a','n','g','e'};

	for (int i=0; i<6; i++)
	{
		if(test_read[i] != array[i])
		{
			return false;
		}
	}
	return true;
}
