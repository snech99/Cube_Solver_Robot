/*
*   Gerrit Hinrichs 01.2025
*   github.com/snech99
*
*   Cube_Solver_Robot
*   State-Machine and all important functions
*/
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
char buf_back[] = "back";
uint8_t busy_msg[1] = {1};

int cube_array[54] = {};

int manual_state_flag = 0;

uint8_t move_count = 0;

uint8_t cube_message[61];

// State-Machine struct with all combinations
State_Transition transitionTable[] =
{
		{config, Taster_T_L, idle_auto, back_to_auto},
		{config, Taster_B_L, idle_man, config_to_man_Handler},
		{idle_auto, Taster_T_L, random_auto, auto_to_random_Handler},
		{idle_auto, Taster_B_L, read_color_auto, auto_to_read_color_Handler},
		{idle_auto, Taster_T_R, solve_auto, auto_to_solve_Handler},
		{idle_auto, Taster_B_R, change_cube, auto_to_change_Handler},
		{solve_auto, Taster_B_R, idle_auto, back_to_auto},
		{solve_auto, Taster_T_L, fast, solve_to_fast_Handler},
		{solve_auto, Taster_B_L, slow, solve_to_slow_Handler},
		{random_auto, Taster_B_R, idle_auto, back_to_auto},
		{read_color_auto, Taster_B_R, idle_auto, back_to_auto},
		{fast, Taster_B_R, idle_auto, back_to_auto},
		{slow, Taster_B_R, idle_auto, back_to_auto},
		{change_cube, Taster_B_R, idle_auto, back_to_auto},

		{idle_man, msg_random, idle_man, man_to_random_Handler},
		{idle_man, msg_read_color, idle_man, man_to_read_color_Handler},
		{idle_man, msg_send_cube, idle_man, man_to_send_cube_Handler},
		{idle_man, msg_solve, idle_man, man_to_solve_Handler},
		{idle_man, msg_change, idle_man, man_to_change_Handler},
};

// State-Machine: from config to external_PC
void config_to_man_Handler(void)
{
	manual_state_flag = 1;

	char buf_1[] = "1:Scan Cube";
	char buf_2[] = "2:Send Cube to PC";
	char buf_5[] = "5:Solve";
	char buf_6[] = "6:20 Random moves";
	char buf_7[] = "7:Change Cube";

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();

	ssd1309_SetCursor(1,1);
	ssd1309_WriteString(buf_1,Font_7x10, White);

	ssd1309_SetCursor(1,13);
	ssd1309_WriteString(buf_2,Font_7x10, White);

	ssd1309_SetCursor(1,25);
	ssd1309_WriteString(buf_5,Font_7x10, White);

	ssd1309_SetCursor(1,37);
	ssd1309_WriteString(buf_6,Font_7x10, White);

	ssd1309_SetCursor(1,49);
	ssd1309_WriteString(buf_7,Font_7x10, White);

	ssd1309_UpdateScreen();
}

// State-Machine: from automatic to random
void auto_to_random_Handler(void)
{
	uint8_t erg = 0;
	uint8_t last = 0;
	uint8_t temp = 0;
	uint8_t pos = 0;

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	while(pos < 20)
	{
		erg = get_rand_num();

		if(erg > 6)
		{
			temp = erg-6;
		}
		else
		{
			temp = erg+6;
		}

		if(temp != last)
		{
			move_motor(erg, 250);
			pos++;
		}
		last = erg;
	}

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(97,51);
	ssd1309_WriteString(buf_back,Font_7x10, White);
	ssd1309_UpdateScreen();
}

// State-Machine: from automatic to Scan Cube
void auto_to_read_color_Handler(void)
{
	GPIO_PinWrite(GPIO2,LED_SWITCH_PIN, 1);

	char buf[] = "scanning ...";
	char buf_e[] = "error";
	char buf_f[] = "correct";

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();
	ssd1309_SetCursor(20,25);
	ssd1309_WriteString(buf, Font_7x10, White);
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
			3,6,7,8,5,2,1,0,
			16,17,14,11,10,9,12,15,
			23,20,19,18,21,24,25,26,
			28,27,30,33,34,35,32,29,
			39,42,43,44,41,38,37,36,
			48,51,46,53,50,47,52,45
	};

	for(uint8_t i=0; i<6; i++)
	{
		PWM_ramp_time = RAMP_SHORT;
		move_servo(15);
		for( uint8_t i=0; i<5; i++)
		{
			pwm_servo_busy_flag = true;
			CTIMER_StartTimer(CTIMER2);
			while(pwm_servo_busy_flag)
			{

			}
		}

		for(uint8_t k=0; k<8; k++)
		{
			color = get_color();
			cube_array [pos_array_read[pos_read]] = color;
			pos_read++;
			move_motor(1, 125);

			for( uint8_t i=0; i<8; i++)
			{
				pwm_servo_busy_flag = true;
				CTIMER_StartTimer(CTIMER2);
				while(pwm_servo_busy_flag)
				{

				}
			}
		}
		PWM_ramp_time = RAMP_LONG;
		move_servo(17);
		change_sides(i);
	}

	GPIO_PinWrite(GPIO2,LED_SWITCH_PIN, 0);
	move_servo(18);

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();

	if(!check_colors())
	{
		for(uint8_t i=0; i<54; i++)
		{
			cube_array[i] = 0;
		}

		ssd1309_SetCursor(30,20);
		ssd1309_WriteString(buf_e, Font_11x18, White);
	}
	else
	{
		ssd1309_SetCursor(25,20);
		ssd1309_WriteString(buf_f, Font_11x18, White);
	}

	ssd1309_SetCursor(97,51);
	ssd1309_WriteString(buf_back,Font_7x10, White);
	ssd1309_UpdateScreen();
}

// State-Machine: from automatic to solve
void auto_to_solve_Handler(void)
{
	char buf_1[] = "fast";
	char buf_2[] = "slow";
	char buf_5[] = "No Cube";

	for( uint8_t i=0; i<200; i++)
	{
		move_array_final[i]={0};
	}

	if(cube_array[0] == 0)
	{
		ssd1309_Fill(Black);
		ssd1309_UpdateScreen();

		ssd1309_SetCursor(20,20);
		ssd1309_WriteString(buf_5, Font_11x18, White);

		ssd1309_SetCursor(97,51);
		ssd1309_WriteString(buf_back,Font_7x10, White);

		ssd1309_UpdateScreen();
	}
	else
	{
		ssd1309_Fill(Black);
		ssd1309_UpdateScreen();

		move_count = do_magic(cube_array, move_array_final);

		ssd1309_SetCursor(2,3);
		ssd1309_WriteString(buf_1,Font_7x10, White);

		ssd1309_SetCursor(2,50);
		ssd1309_WriteString(buf_2,Font_7x10, White);

		ssd1309_SetCursor(97,51);
		ssd1309_WriteString(buf_back,Font_7x10, White);

		ssd1309_UpdateScreen();
	}
}

// State-Machine: from automatic to fast
void solve_to_fast_Handler(void)
{
	char print_moves_num [4] = {};
	char print_time_sec [4] = {};
	char print_time_ms [4] = {};

	char s_print[] = "sec";
	char moves_in[] = "moves";
	uint8_t offset = 0;
	uint32_t pos = 0;
	uint32_t time = 0;
	uint32_t time_ms = 0;

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	tick_start = tick_count;

	while(move_array_final[pos] != 0)
	{
		move_motor(move_array_final[pos], 250);
		pos++;
	}

	tick_end = tick_count;
	time = calc_time_ms();

	time_ms = time%1000;
	time = time/1000;

	if(time > 99)
	{
		offset = 7;
	}

	itoa(move_count,print_moves_num, 10);
	itoa(time,print_time_sec, 10);
	itoa(time_ms,print_time_ms, 10);

	for( uint8_t i=0; i<200; i++)
	{
		move_array_final[i]={0};
	}

	for(uint8_t i=0; i<54; i++)
	{
		cube_array[i] = 0;
	}

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	ssd1309_SetCursor(20,10);
	ssd1309_WriteString(print_moves_num, Font_7x10, White);

	ssd1309_SetCursor(60,10);
	ssd1309_WriteString(moves_in, Font_7x10, White);

	ssd1309_SetCursor(20,40);
	ssd1309_WriteString(print_time_sec, Font_7x10, White);

	ssd1309_SetCursor(34+offset,40);
	ssd1309_WriteString(",", Font_7x10, White);

	ssd1309_SetCursor(41+offset,40);
	ssd1309_WriteString(print_time_ms, Font_7x10, White);

	ssd1309_SetCursor(65+offset,40);
	ssd1309_WriteString(s_print, Font_7x10, White);

	ssd1309_SetCursor(97,53);
	ssd1309_WriteString(buf_back,Font_7x10, White);

	ssd1309_UpdateScreen();
}

// State-Machine: from automatic to slow
void solve_to_slow_Handler(void)
{
	char print_moves_num [4] = {};
	char print_time_sec [4] = {};
	char print_time_ms [4] = {};

	char s_print[] = "sec";
	char moves_in[] = "moves";
	uint8_t offset = 0;
	uint32_t pos = 0;
	uint32_t time = 0;
	uint32_t time_ms = 0;

	PWM_frequenz = 2000;

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	tick_start = tick_count;

	while(move_array_final[pos] != 0)
	{
		move_motor(move_array_final[pos], 250);

		for(uint8_t i=0; i<10; i++)
		{
			pwm_busy_flag = true;
			CTIMER_StartTimer(CTIMER2);
			while(pwm_busy_flag)
			{

			}
		}
		pos++;
	}

	PWM_frequenz = PWM_FREQUENZ;

	tick_end = tick_count;
	time = calc_time_ms();

	time_ms = time%1000;
	time = time/1000;

	if(time > 99)
	{
		offset = 7;
	}

	itoa(move_count,print_moves_num, 10);
	itoa(time,print_time_sec, 10);
	itoa(time_ms,print_time_ms, 10);

	for( uint8_t i=0; i<200; i++)
	{
		move_array_final[i]={0};
	}

	for(uint8_t i=0; i<54; i++)
	{
		cube_array[i] = 0;
	}

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	ssd1309_SetCursor(20,10);
	ssd1309_WriteString(print_moves_num, Font_7x10, White);

	ssd1309_SetCursor(60,10);
	ssd1309_WriteString(moves_in, Font_7x10, White);

	ssd1309_SetCursor(20,40);
	ssd1309_WriteString(print_time_sec, Font_7x10, White);

	ssd1309_SetCursor(34+offset,40);
	ssd1309_WriteString(",", Font_7x10, White);

	ssd1309_SetCursor(41+offset,40);
	ssd1309_WriteString(print_time_ms, Font_7x10, White);

	ssd1309_SetCursor(65+offset,40);
	ssd1309_WriteString(s_print, Font_7x10, White);

	ssd1309_SetCursor(97,51);
	ssd1309_WriteString(buf_back,Font_7x10, White);

	ssd1309_UpdateScreen();
}

// State-Machine: from automatic to change Cube
void auto_to_change_Handler (void)
{
	char buf_1[] = "Change done";

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();

	ssd1309_SetCursor(2,3);
	ssd1309_WriteString(buf_1,Font_7x10, White);

	ssd1309_UpdateScreen();

    GPIO_PinWrite(MOTOR_EN_GPIO, MOTOR_EN_PIN, M_DISABLE);

	while(!SW_flag_TL)
	{

	}
	SW_flag_TL = false;

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();

	GPIO_PinWrite(MOTOR_EN_GPIO, MOTOR_EN_PIN, M_ENABLE);

	config_motor();

	ssd1309_SetCursor(97,51);
	ssd1309_WriteString(buf_back,Font_7x10, White);

	ssd1309_UpdateScreen();
}

// State-Machine: return from function to automatic
void back_to_auto(void)
{
	char buf_1[] = "Random";
	char buf_2[] = "Scan";
	char buf_3[] = "Solve";
	char buf_4[] = "Change";

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();

	ssd1309_SetCursor(2,3);
	ssd1309_WriteString(buf_1,Font_7x10, White);

	ssd1309_SetCursor(2,51);
	ssd1309_WriteString(buf_2,Font_7x10, White);

	ssd1309_SetCursor(90,3);
	ssd1309_WriteString(buf_3,Font_7x10, White);

	ssd1309_SetCursor(85,51);
	ssd1309_WriteString(buf_4,Font_7x10, White);

	ssd1309_UpdateScreen();
}

// State-Machine: from external_PC to random
void man_to_random_Handler(void)
{
	uint8_t erg = 0;
	uint8_t last = 0;
	uint8_t temp = 0;
	uint8_t pos = 0;

	while(pos < 20)
	{
		erg = get_rand_num();

		if(erg > 6)
		{
			temp = erg-6;
		}
		else
		{
			temp = erg+6;
		}

		if(temp != last)
		{
			move_motor(erg, 250);
			pos++;
		}
		last = erg;
	}

	LPUART_WriteBlocking(LPUART2_PERIPHERAL, busy_msg, sizeof(busy_msg));
	config_to_man_Handler();
}

// State-Machine: from external_PC to Scan Cube
void man_to_read_color_Handler(void)
{
	GPIO_PinWrite(GPIO2,LED_SWITCH_PIN, 1);

	char buf[] = "scanning ...";
	char buf_e[] = "error";
	char buf_f[] = "correct";

    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();
	ssd1309_SetCursor(20,25);
	ssd1309_WriteString(buf, Font_7x10, White);
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
			3,6,7,8,5,2,1,0,
			16,17,14,11,10,9,12,15,
			23,20,19,18,21,24,25,26,
			28,27,30,33,34,35,32,29,
			39,42,43,44,41,38,37,36,
			48,51,46,53,50,47,52,45
	};

	for(uint8_t i=0; i<6; i++)
	{
		move_servo(15);
		for( uint8_t i=0; i<5; i++)
		{
			pwm_servo_busy_flag = true;
			CTIMER_StartTimer(CTIMER2);
			while(pwm_servo_busy_flag)
			{

			}
		}

		PWM_ramp_time = RAMP_SHORT;
		for( uint8_t i=0; i<5; i++)
		{
			pwm_servo_busy_flag = true;
			CTIMER_StartTimer(CTIMER2);
			while(pwm_servo_busy_flag)
			{

			}
		}
		for(uint8_t k=0; k<8; k++)
		{
			color = get_color();
			cube_array [pos_array_read[pos_read]] = color;
			pos_read++;
			move_motor(1, 125);

			for( uint8_t i=0; i<8; i++)
			{
				pwm_servo_busy_flag = true;
				CTIMER_StartTimer(CTIMER2);
				while(pwm_servo_busy_flag)
				{

				}
			}
		}

		PWM_ramp_time = RAMP_LONG;
		move_servo(17);
		change_sides(i);
	}

	GPIO_PinWrite(GPIO2,LED_SWITCH_PIN, 0);
	move_servo(18);

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();
	ssd1309_SetCursor(25,20);

	if(!check_colors())
	{
		ssd1309_WriteString(buf_e, Font_11x18, White);

		for(uint8_t i=0; i<54; i++)
		{
			cube_array[i] = 0;
		}
	}
	else
	{
		ssd1309_WriteString(buf_f, Font_11x18, White);
	}
	ssd1309_UpdateScreen();

	LPUART_WriteBlocking(LPUART2_PERIPHERAL, busy_msg, sizeof(busy_msg));
}

// State-Machine: from external_PC to send Cube
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

	LPUART_WriteBlocking(LPUART2_PERIPHERAL, cube_message, sizeof(cube_message));
	config_to_man_Handler();
	LPUART_WriteBlocking(LPUART2_PERIPHERAL, busy_msg, sizeof(busy_msg));
}

// State-Machine: from external_PC to solve
void man_to_solve_Handler(void)
{
	char print_moves_num [4] = {};
	char print_time_sec [4] = {};
	char print_time_ms [4] = {};

	char s_print[] = "sec";
	char moves_in[] = "moves";
	uint32_t erg = 0;
	uint8_t offset = 0;
	uint32_t time = 0;
	uint32_t time_ms = 0;

	char buf[] = "solving ..";

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

 	tick_start = tick_count;

	while(msg.m_data[erg] != 0)
	{
		move_motor(msg.m_data[erg], 250);
		erg++;
	}

	tick_end = tick_count;
	time = calc_time_ms();

	for (int i=0; i<54; i++)
	{
		cube_array[i] = 0;
	}

	time_ms = time%1000;
	time = time/1000;

	if(time > 99)
	{
		offset = 7;
	}

	itoa(erg,print_moves_num, 10);
	itoa(time,print_time_sec, 10);
	itoa(time_ms,print_time_ms, 10);

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	ssd1309_SetCursor(20,10);
	ssd1309_WriteString(print_moves_num, Font_7x10, White);

	ssd1309_SetCursor(60,10);
	ssd1309_WriteString(moves_in, Font_7x10, White);

	ssd1309_SetCursor(20,40);
	ssd1309_WriteString(print_time_sec, Font_7x10, White);

	ssd1309_SetCursor(34+offset,40);
	ssd1309_WriteString(",", Font_7x10, White);

	ssd1309_SetCursor(41+offset,40);
	ssd1309_WriteString(print_time_ms, Font_7x10, White);

	ssd1309_SetCursor(65+offset,40);
	ssd1309_WriteString(s_print, Font_7x10, White);

	ssd1309_UpdateScreen();

	LPUART_WriteBlocking(LPUART2_PERIPHERAL, busy_msg, sizeof(busy_msg));
}

// State-Machine: from external_PC to change Cube
void man_to_change_Handler(void)
{
	char buf_1[] = "Change done";

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	ssd1309_SetCursor(2,3);
	ssd1309_WriteString(buf_1,Font_7x10, White);

	ssd1309_UpdateScreen();

	GPIO_PinWrite(MOTOR_EN_GPIO, MOTOR_EN_PIN, M_DISABLE);

	while(!SW_flag_TL)
	{

	}
	SW_flag_TL = false;

	ssd1309_Fill(Black);
	ssd1309_UpdateScreen();

	GPIO_PinWrite(MOTOR_EN_GPIO, MOTOR_EN_PIN, M_ENABLE);

	config_motor();

	LPUART_WriteBlocking(LPUART2_PERIPHERAL, busy_msg, sizeof(busy_msg));

	config_to_man_Handler();
}

// Function which checks for a new event (Button or Message)
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

			case change:
				return msg_change;

			default:
				break;
		}
	}
	return default_event;
}

// Function which checks for a suitable State and Event
void runStateMachine(Event_t event)
{
    for (uint8_t i = 0; i < sizeof(transitionTable) / sizeof(transitionTable[0]); i++)
    {
        if (transitionTable[i].current_state == CURRENT_STATE && transitionTable[i].event == event)
        {
            transitionTable[i].action();
            CURRENT_STATE = transitionTable[i].next_state;
            flag_hit_2 = false;
        }
    }
}

// Function called in the super-loop
void super_machine()
{
	Event_t currentEvent = get_new_Event();
    runStateMachine(currentEvent);
}
