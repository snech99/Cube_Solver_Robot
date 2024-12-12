#include "Cube_Project.h"
#include "state_machine.h"
#include "Adafruit_TCS34725.h"
#include "solver_algorithmus_new\example_cubes.h"
#include "solver_algorithmus_new\do_magic.h"
#include <ssd1309/ssd1309.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_240MS, TCS34725_GAIN_1X);
State_t CURRENT_STATE = config;
message msg;
int move_array_final [200] = {};
int *ptr_array_final = move_array_final;
bool pwm_servo_busy_flag = false;

char buf_name_white[] = "weiss";
char buf_name_yellow[] = "gelb";
char buf_name_red[] = "rot";
char buf_name_green[] = "gruen";
char buf_name_orange[] = "orange";
char buf_name_blue[] = "blau";

char buf_back[] = "back";

int cube_array[54] = {};

uint8_t cube_message[61];

State_Transition transitionTable[] =
{
		{config, Taster_T_L, idle_auto, back_to_auto},
		{config, Taster_B_L, idle_man, config_to_man_Handler},
		{idle_auto, Taster_T_L, random_auto, auto_to_random_Handler},
		{idle_auto, Taster_B_L, read_color_auto, auto_to_read_color_Handler},
		{idle_auto, Taster_T_R, solve_auto, auto_to_solve_Handler},
		{solve_auto, Taster_B_R, idle_auto, back_to_auto},
		{solve_auto, Taster_T_L, fast, solve_to_fast_Handler},
		{solve_auto, Taster_B_L, slow, solve_to_slow_Handler},
		{random_auto, Taster_B_R, idle_auto, back_to_auto},
		{read_color_auto, Taster_B_R, idle_auto, back_to_auto},
		{fast, Taster_B_R, idle_auto, back_to_auto},
		{slow, Taster_B_R, idle_auto, back_to_auto},

		{idle_man, msg_random, idle_man, man_to_random_Handler},
		{idle_man, msg_read_color, idle_man, man_to_read_color_Handler},
		{idle_man, msg_send_cube, idle_man, man_to_send_cube_Handler},
		{idle_man, msg_solve, idle_man, man_to_solve_Handler},
};

void config_to_man_Handler(void)
{
	char buf[] = "man";

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();
	ssd1309_SetCursor(33,30);
	ssd1309_WriteString(buf,Font_7x10, White);
	ssd1309_UpdateScreen();
}

void auto_to_random_Handler(void)
{
	move_motor(1,250);
	move_motor(7,250);
	move_motor(2,250);
	move_motor(8,250);
	move_motor(3,250);
	move_motor(9,250);
	move_motor(4,250);
	move_motor(10,250);
	move_motor(5,250);
	move_motor(11,250);
	move_motor(6,250);
	move_motor(12,250);

	/*
	uint8_t erg = get_rand_num();
	char print_num[] =  {'0'};

	itoa(erg,print_num, 10);

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	ssd1309_SetCursor(52,20);
	ssd1309_WriteString(print_num, Font_11x18, White);
	ssd1309_SetCursor(85,51);
	ssd1309_WriteString(buf_back,Font_7x10, White);
	ssd1309_UpdateScreen();
	*/
}

void auto_to_read_color_Handler(void)
{
	GPIO_PinWrite(GPIO2,LED_SWITCH_PIN, 1);

	char buf[] = "scan";

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();
	ssd1309_SetCursor(33,20);
	ssd1309_WriteString(buf, Font_11x18, White);
    ssd1309_UpdateScreen();

	cube_array [4] = 1;
	cube_array [13] = 3;
	cube_array [22] = 6;
	cube_array [31] = 5;
	cube_array [40] = 4;
	cube_array [49] = 2;

	uint8_t color;
	uint8_t pos_read = 0;

	volatile uint8_t pos_array_read[48] =
	{
			4,7,8,9,6,3,2,1,
			17,18,15,12,11,10,13,16,
			24,27,26,25,22,19,20,21,
			29,28,31,34,35,36,33,30,
			40,43,44,45,42,39,38,37,
			49,52,47,54,51,48,53,46
	};

	move_servo(18);

	for(uint8_t i=0; i<6; i++)
	{
		for(uint8_t k=0; k<8; k++)
		{
			move_servo(15);
			color = get_color();
			cube_array [pos_array_read[pos_read]-1] = color;
			pos_read++;
			move_servo(16);
			move_motor(7, 125);
		}

		move_servo(18);
		change_sides(i);
	}

	if(!check_colors())
	{
		for(uint8_t i=0; i<54; i++)
		{
			cube_array[i] = 0;
		}
	}


	GPIO_PinWrite(GPIO2,LED_SWITCH_PIN, 0);
	ssd1309_SetCursor(85,51);
	ssd1309_WriteString(buf_back,Font_7x10, White);
	ssd1309_UpdateScreen();

}

void auto_to_solve_Handler(void)
{
	char buf_1[] = "schnell";
	char buf_2[] = "langsam";
	char buf_3[] = "error";

	char print_moves_num [3] = {};
	char print_time_num [3] = {};
	char ms_print[] = "ms";
	uint32_t erg = 0;
	uint32_t time = 0;

	//set_bsp_02();
	//set_bsp_03();
	//set_bsp_04();

	for( uint8_t i=0; i<200; i++)
	{
		move_array_final[i]={0};
	}

	if(cube_array[0] == 0)
	{
		ssd1309_Fill(Black);
		ssd1309_UpdateScreen();

		ssd1309_SetCursor(68,20);
		ssd1309_WriteString(buf_3, Font_11x18, White);

		ssd1309_SetCursor(2,3);
		ssd1309_WriteString(buf_1,Font_7x10, White);

		ssd1309_SetCursor(2,50);
		ssd1309_WriteString(buf_2,Font_7x10, White);

		ssd1309_SetCursor(85,51);
		ssd1309_WriteString(buf_back,Font_7x10, White);

		ssd1309_UpdateScreen();
	}
	else
	{
		tick_start = tick_count;
		erg = do_magic(cube_array, move_array_final);
		tick_end = tick_count;

		time = calc_time_ms();

		itoa(erg,print_moves_num, 10);
		itoa(time,print_time_num, 10);

		ssd1309_Fill(Black);
		ssd1309_UpdateScreen();

		ssd1309_SetCursor(80,3);
		ssd1309_WriteString(print_moves_num, Font_11x18, White);

		ssd1309_SetCursor(56,20);
		ssd1309_WriteString(print_time_num, Font_11x18, White);

		ssd1309_SetCursor(90,20);
		ssd1309_WriteString(ms_print, Font_11x18, White);

		ssd1309_SetCursor(2,3);
		ssd1309_WriteString(buf_1,Font_7x10, White);

		ssd1309_SetCursor(2,50);
		ssd1309_WriteString(buf_2,Font_7x10, White);

		ssd1309_SetCursor(85,51);
		ssd1309_WriteString(buf_back,Font_7x10, White);

		ssd1309_UpdateScreen();
	}
}

void solve_to_fast_Handler(void)
{
	PWM_frequenz = 8000;

	uint16_t pos = 0;

	while(move_array_final[pos] != 0)
	{
		move_motor(move_array_final[pos], 250);
		pos++;
	}

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(85,51);
	ssd1309_WriteString(buf_back,Font_7x10, White);
	ssd1309_UpdateScreen();
}

void solve_to_slow_Handler(void)
{
	uint16_t pos = 0;

	PWM_frequenz = 2000;

	while(move_array_final[pos] != 0)
	{
		move_motor(move_array_final[pos], 250);
		pos++;
	}

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(85,51);
	ssd1309_WriteString(buf_back,Font_7x10, White);
	ssd1309_UpdateScreen();
}

void back_to_auto(void)
{
	char buf_1[] = "verdrehen";
	char buf_2[] = "Cube einlesen";
	char buf_3[] = "loesen";

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();

	ssd1309_SetCursor(2,3);
	ssd1309_WriteString(buf_1,Font_7x10, White);

	ssd1309_SetCursor(2,51);
	ssd1309_WriteString(buf_2,Font_7x10, White);

	ssd1309_SetCursor(80,3);
	ssd1309_WriteString(buf_3,Font_7x10, White);

	ssd1309_UpdateScreen();
}

void man_to_random_Handler(void)
{
	uint8_t erg;

	/*
	for(uint8_t i=0; i<20; i++)
	{
		erg = get_rand_num();
		move_motor(erg, 250);
	}
	*/

	char buf[] = "6";

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(60,30);
	ssd1309_WriteString(buf,Font_7x10, White);
	ssd1309_UpdateScreen();
}

void man_to_read_color_Handler(void)
{
	GPIO_PinWrite(GPIO2,LED_SWITCH_PIN, 1);

	char buf[] = "scan";

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(33,20);
	ssd1309_WriteString(buf, Font_11x18, White);
	ssd1309_UpdateScreen();

	cube_array [4] = 1;
	cube_array [13] = 3;
	cube_array [22] = 6;
	cube_array [31] = 5;
	cube_array [40] = 4;
	cube_array [49] = 2;

	uint8_t color;
	uint8_t pos_read = 0;

	volatile uint8_t pos_array_read[48] =
	{
			4,7,8,9,6,3,2,1,
			17,18,15,12,11,10,13,16,
			24,27,26,25,22,19,20,21,
			29,28,31,34,35,36,33,30,
			40,43,44,45,42,39,38,37,
			49,52,47,54,51,48,53,46
	};

	move_servo(18);

	for(uint8_t i=0; i<6; i++)
	{
		for(uint8_t k=0; k<8; k++)
		{
			move_servo(15);
			color = get_color();
			cube_array [pos_array_read[pos_read]-1] = color;
			pos_read++;
			move_servo(16);
			move_motor(7, 125);
		}

		move_servo(18);
		change_sides(i);
	}

	char buf_e[] = "err";
	char buf_f[] = "correct";

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(33,20);

	if(!check_colors())
	{
		ssd1309_WriteString(buf_e, Font_11x18, White);
		/*
		for(uint8_t i=0; i<54; i++)
		{
			cube_array[i] = 0;
		}
		*/
	}
	else
	{
		ssd1309_WriteString(buf_f, Font_11x18, White);
	}
	ssd1309_UpdateScreen();
}

void man_to_send_cube_Handler(void)
{
	cube_message[0] = '$';
	cube_message[1] = 'c';
	cube_message[2] = 'u';
	cube_message[3] = 'b';
	cube_message[4] = 'e';
	cube_message[5] = '!';
	cube_message[60] = '%';

	for (int i=6; i<=59; i++)
	{
		cube_message[i] = cube_array[i-6];
	}

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	LPUART_WriteBlocking(LPUART2_PERIPHERAL, cube_message, sizeof(cube_message));
}

void man_to_solve_Handler(void)
{
	uint16_t erg = 0;

	char buf[] = "5";

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(60,30);
	ssd1309_WriteString(buf,Font_7x10, White);
	ssd1309_UpdateScreen();
/*
	for(uint8_t i=0; i<245; i++)
	{
		if(msg.data != 0)
		{
			move_motor(msg.data[i]);
			erg++;
		}
		else
		{
			break;
		}
	}

	for (int i=0; i<54; i++)
	{
		cube_array[i] = 0;
	}

	char buf[] = {(char)erg}

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(60,30);
	ssd1309_WriteString(buf,Font_7x10, White);
	ssd1309_UpdateScreen();
*/
}


Event_t get_new_Event(void)
{
	if(SW_flag_TL)
	{
		SW_flag_TL = false;
		SW_flag_BL = false;
		SW_flag_TR = false;
		SW_flag_BR = false;

		return Taster_T_L;
	}

	if(SW_flag_BL)
	{
		SW_flag_TL = false;
		SW_flag_BL = false;
		SW_flag_TR = false;
		SW_flag_BR = false;

		return Taster_B_L;
	}

	if(SW_flag_TR)
	{
		SW_flag_TL = false;
		SW_flag_BL = false;
		SW_flag_TR = false;
		SW_flag_BR = false;

		return Taster_T_R;
	}

	if(SW_flag_BR)
	{
		SW_flag_TL = false;
		SW_flag_BL = false;
		SW_flag_TR = false;
		SW_flag_BR = false;

		return Taster_B_R;
	}

	if(flag_hit_2)
	{
		command current_state = err;
		flag_hit_2 = false;
		flag_hit_1 = false;
		msg = get_command_and_data(rx_buffer);
		current_state = msg.m_command;

		rx_buffer_index = 0;

		switch(current_state)
		{
			case send_cube:
				return msg_send_cube;

			case read_color:
				return msg_read_color;

			case solve:
				return msg_solve;

			case com_random:
				return msg_random;

			default:
				break;
		}
	}
	return default_event;
}

void runStateMachine(Event_t event)
{

    for (uint8_t i = 0; i < sizeof(transitionTable) / sizeof(transitionTable[0]); i++)
    {
        if (transitionTable[i].current_state == CURRENT_STATE && transitionTable[i].event == event)
        {
            transitionTable[i].action();
            CURRENT_STATE = transitionTable[i].next_state;
            return;
        }
    }
}

void super_machine()
{
	Event_t currentEvent = get_new_Event();
    runStateMachine(currentEvent);
}
