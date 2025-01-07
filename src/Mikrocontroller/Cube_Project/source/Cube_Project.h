/*
 * Cube_Project.h
 *
 *  Created on: 05.10.2024
 *      Author: gerri
 */
#include "fsl_common.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "Adafruit_TCS34725.h"
#include <ssd1309/ssd1309.h>
#include <ssd1309/ssd1309_fonts.h>

#ifndef CUBE_PROJECT_H_
#define CUBE_PROJECT_H_

#define PWM_FREQUENZ 10000
#define RAMP_LONG 40
#define RAMP_SHORT 20

#define BUFFER_MAX 1033
#define SW_3_PIN BOARD_INITSW_SW_3_PIN
#define TASTER_T_L BOARD_INITSW_TASTER_T_L_PIN
#define TASTER_T_R BOARD_INITSW_TASTER_T_R_PIN
#define TASTER_B_L BOARD_INITSW_TASTER_B_L_PIN
#define TASTER_B_R BOARD_INITSW_TASTER_B_R_PIN

#define INTERUPT_SENSOR_PIN BOARD_INITSW_INTERUPT_SENSOR_GPIO_PIN
#define CTIMER_OUT_VAL  (1u << kCTIMER_Match_0)
#define I2C_ADDR_SENSOR 0x29
#define I2C_ADDR_SCREEN 0x3C

#define DIR_WHITE_PIN BOARD_INITPWM_DIR_white_PIN
#define DIR_YELLOW_PIN BOARD_INITPWM_DIR_yellow_PIN
#define DIR_RED_PIN BOARD_INITPWM_DIR_red_PIN
#define DIR_GREEN_PIN BOARD_INITPWM_DIR_green_PIN
#define DIR_ORANGE_PIN BOARD_INITPWM_DIR_orange_PIN
#define DIR_BLUE_PIN BOARD_INITPWM_DIR_blue_PIN

#define DIR_WHITE_GPIO BOARD_INITPWM_DIR_white_GPIO
#define DIR_YELLOW_GPIO BOARD_INITPWM_DIR_yellow_GPIO
#define DIR_RED_GPIO BOARD_INITPWM_DIR_red_GPIO
#define DIR_GREEN_GPIO BOARD_INITPWM_DIR_green_GPIO
#define DIR_ORANGE_GPIO BOARD_INITPWM_DIR_orange_GPIO
#define DIR_BLUE_GPIO BOARD_INITPWM_DIR_blue_GPIO

#define EN_WHITE_PIN BOARD_INITPWM_EN_WHITE_PIN
#define EN_YELLOW_PIN BOARD_INITPWM_EN_YELLOW_PIN
#define EN_RED_PIN BOARD_INITPWM_EN_RED_PIN
#define EN_GREEN_PIN BOARD_INITPWM_EN_GREEN_PIN
#define EN_ORANGE_PIN BOARD_INITPWM_EN_ORANGE_PIN
#define EN_BLUE_PIN BOARD_INITPWM_EN_BLUE_PIN

#define EN_WHITE_GPIO BOARD_INITPWM_EN_WHITE_GPIO
#define EN_YELLOW_GPIO BOARD_INITPWM_EN_YELLOW_GPIO
#define EN_RED_GPIO BOARD_INITPWM_EN_RED_GPIO
#define EN_GREEN_GPIO BOARD_INITPWM_EN_GREEN_GPIO
#define EN_ORANGE_GPIO BOARD_INITPWM_EN_ORANGE_GPIO
#define EN_BLUE_GPIO BOARD_INITPWM_EN_BLUE_GPIO

#define LED_SWITCH_PIN BOARD_INITSW_LED_SWITCH_PIN

#define NULL_TRIGGER_GPIO BOARD_INITPWM_NULL_TRIGGER_GPIO
#define NULL_TRIGGER_PIN BOARD_INITPWM_NULL_TRIGGER_PIN

#define LEFT 1
#define RIGHT 0

enum command
{
	com_random = 1,
	solve = 2,
	read_color = 3,
	send_cube = 4,
	moves = 5,
	menu = 6,
	err = 99,
};

enum color_c
{
	c_white = 1,
	c_yellow = 2,
	c_red = 3,
	c_green = 4,
	c_orange = 5,
	c_blue = 6,
};

struct message
{
	command m_command;
	uint8_t m_data[1024] = {};
};

extern volatile uint8_t pos_array_read[48];
extern volatile uint32_t PWM_frequenz;
extern volatile uint32_t pwm_ms_count;
extern volatile int32_t PWM_flanke_count;
extern volatile uint32_t PWM_ramp_time;

extern uint8_t rx_buffer[BUFFER_MAX];
extern uint16_t rx_buffer_index;
extern bool flag_hit_1;
extern bool flag_hit_2 ;
extern bool SW_hit_flag;
extern bool SW_flag_TL;
extern bool SW_flag_TR;
extern bool SW_flag_BL;
extern bool SW_flag_BR;
extern bool color_busy_flag;
extern bool pwm_busy_flag;
extern bool pwm_servo_busy_flag;
extern bool NULL_flag;

extern int cube_array[54];

extern uint32_t tick_count;
extern uint32_t tick_start;
extern uint32_t tick_end;

extern Adafruit_TCS34725 tcs;

struct message get_command_and_data (uint8_t *);
color_c detect_color(uint16_t, uint16_t, uint16_t, uint16_t);
void move_motor(uint8_t, uint8_t);
uint8_t get_rand_num();
uint8_t get_color();
void move_servo(uint8_t);
void change_sides(uint8_t);
bool check_colors();
uint32_t calc_time_ms();
void config_motor();


#endif /* CUBE_PROJECT_H_ */
