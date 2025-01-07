/*
 * motor.cpp
 *
 *  Created on: 29.10.2024
 *      Author: gerri
 */

#include "Cube_Project.h"

void config_motor()
{
	uint8_t config_count = 0;

	move_servo(18);

	while( GPIO_PinRead(NULL_TRIGGER_GPIO, NULL_TRIGGER_PIN) == 0)
	{
		move_motor(1, 250);
		move_motor(2, 250);
		move_motor(3, 250);
		move_motor(4, 250);
		move_motor(5, 250);
		move_motor(6, 250);
	}

	PWM_flanke_count = 5;
	PWM_SetupPwm(FLEXPWM0_PERIPHERAL, FLEXPWM0_ALL_PWM, FLEXPWM0_ALL_PWM_pwm_function_config, 1U, kPWM_SignedCenterAligned,
						500, FLEXPWM0_ALL_PWM_SM_CLK_SOURCE_FREQ_HZ);

	FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_LDOK(kPWM_Control_Module_0);
	FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_RUN(kPWM_Control_Module_0);

	pwm_busy_flag = true;

	while(pwm_busy_flag)
	{

	}

	for(uint8_t i=1; i<=6; i++)
	{
		switch (i)
		{
			case 1: 	GPIO_PinWrite(DIR_WHITE_GPIO, DIR_WHITE_PIN, 0);
						GPIO_PinWrite(EN_WHITE_GPIO, EN_WHITE_PIN, 1);
						config_count = 21;
						break;

			case 2:		GPIO_PinWrite(DIR_YELLOW_GPIO, DIR_YELLOW_PIN, 1);
						GPIO_PinWrite(EN_YELLOW_GPIO, EN_YELLOW_PIN, 1);
						config_count = 118;
						break;

			case 3:		GPIO_PinWrite(DIR_RED_GPIO, DIR_RED_PIN, 0);
						GPIO_PinWrite(EN_RED_GPIO, EN_RED_PIN, 1);
						config_count = 19;
						break;

			case 4:		GPIO_PinWrite(DIR_GREEN_GPIO, DIR_GREEN_PIN, 0);
						GPIO_PinWrite(EN_GREEN_GPIO, EN_GREEN_PIN, 1);
						config_count = 68;
						break;

			case 5:		GPIO_PinWrite(DIR_ORANGE_GPIO, DIR_ORANGE_PIN, 1);
						GPIO_PinWrite(EN_ORANGE_GPIO, EN_ORANGE_PIN, 1);
						config_count = 124;
						break;

			case 6:		GPIO_PinWrite(DIR_BLUE_GPIO, DIR_BLUE_PIN, 0);
						GPIO_PinWrite(EN_BLUE_GPIO, EN_BLUE_PIN, 1);
						config_count = 63;
						break;
			default:
				break;
		}

		PWM_flanke_count = 2000;

		PWM_SetupPwm(FLEXPWM0_PERIPHERAL, FLEXPWM0_ALL_PWM, FLEXPWM0_ALL_PWM_pwm_function_config, 1U, kPWM_SignedCenterAligned,
							1000, FLEXPWM0_ALL_PWM_SM_CLK_SOURCE_FREQ_HZ);

		FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_LDOK(kPWM_Control_Module_0);
		FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_RUN(kPWM_Control_Module_0);

		NULL_flag = false;

		while(!NULL_flag)
		{

		}

		FLEXPWM0_PERIPHERAL->MCTRL &= ~(PWM_MCTRL_RUN(kPWM_Control_Module_0));

		PWM_flanke_count = config_count;

		PWM_SetupPwm(FLEXPWM0_PERIPHERAL, FLEXPWM0_ALL_PWM, FLEXPWM0_ALL_PWM_pwm_function_config, 1U, kPWM_SignedCenterAligned,
									1000, FLEXPWM0_ALL_PWM_SM_CLK_SOURCE_FREQ_HZ);

		FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_LDOK(kPWM_Control_Module_0);
		FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_RUN(kPWM_Control_Module_0);

		pwm_busy_flag = true;

		while(pwm_busy_flag)
		{

		}

		FLEXPWM0_PERIPHERAL->MCTRL &= ~(PWM_MCTRL_RUN(kPWM_Control_Module_0));

	 	GPIO_PinWrite(EN_WHITE_GPIO, EN_WHITE_PIN, 0);
		GPIO_PinWrite(EN_YELLOW_GPIO, EN_YELLOW_PIN, 0);
		GPIO_PinWrite(EN_RED_GPIO, EN_RED_PIN, 0);
		GPIO_PinWrite(EN_GREEN_GPIO, EN_GREEN_PIN, 0);
		GPIO_PinWrite(EN_ORANGE_GPIO, EN_ORANGE_PIN, 0);
		GPIO_PinWrite(EN_BLUE_GPIO, EN_BLUE_PIN, 0);
	}
}

void move_motor(uint8_t num, uint8_t flank)
{
	pwm_busy_flag = true;
	PWM_flanke_count = flank;
	pwm_ms_count = 0;

	switch (num)
	{
		case 1: 	GPIO_PinWrite(DIR_WHITE_GPIO, DIR_WHITE_PIN, 1);
					GPIO_PinWrite(EN_WHITE_GPIO, EN_WHITE_PIN, 1);
					break;

		case 2:		GPIO_PinWrite(DIR_YELLOW_GPIO, DIR_YELLOW_PIN, 1);
					GPIO_PinWrite(EN_YELLOW_GPIO, EN_YELLOW_PIN, 1);
					break;

		case 3:		GPIO_PinWrite(DIR_RED_GPIO, DIR_RED_PIN, 1);
					GPIO_PinWrite(EN_RED_GPIO, EN_RED_PIN, 1);
					break;

		case 4:		GPIO_PinWrite(DIR_GREEN_GPIO, DIR_GREEN_PIN, 1);
					GPIO_PinWrite(EN_GREEN_GPIO, EN_GREEN_PIN, 1);
					break;

		case 5:		GPIO_PinWrite(DIR_ORANGE_GPIO, DIR_ORANGE_PIN, 1);
					GPIO_PinWrite(EN_ORANGE_GPIO, EN_ORANGE_PIN, 1);
					break;

		case 6:		GPIO_PinWrite(DIR_BLUE_GPIO, DIR_BLUE_PIN, 1);
					GPIO_PinWrite(EN_BLUE_GPIO, EN_BLUE_PIN, 1);
					break;

		case 7: 	GPIO_PinWrite(DIR_WHITE_GPIO, DIR_WHITE_PIN, 0);
					GPIO_PinWrite(EN_WHITE_GPIO, EN_WHITE_PIN, 1);
					break;

		case 8:		GPIO_PinWrite(DIR_YELLOW_GPIO, DIR_YELLOW_PIN, 0);
					GPIO_PinWrite(EN_YELLOW_GPIO, EN_YELLOW_PIN, 1);
					break;

		case 9:		GPIO_PinWrite(DIR_RED_GPIO, DIR_RED_PIN, 0);
					GPIO_PinWrite(EN_RED_GPIO, EN_RED_PIN, 1);
					break;

		case 10:	GPIO_PinWrite(DIR_GREEN_GPIO, DIR_GREEN_PIN, 0);
					GPIO_PinWrite(EN_GREEN_GPIO, EN_GREEN_PIN, 1);
					break;

		case 11:	GPIO_PinWrite(DIR_ORANGE_GPIO, DIR_ORANGE_PIN, 0);
					GPIO_PinWrite(EN_ORANGE_GPIO, EN_ORANGE_PIN, 1);
					break;

		case 12:	GPIO_PinWrite(DIR_BLUE_GPIO, DIR_BLUE_PIN, 0);
					GPIO_PinWrite(EN_BLUE_GPIO, EN_BLUE_PIN, 1);
					break;
		default:
			break;
	}

	PWM_SetupPwm(FLEXPWM0_PERIPHERAL, FLEXPWM0_ALL_PWM, FLEXPWM0_ALL_PWM_pwm_function_config, 1U, kPWM_SignedCenterAligned,
						200, FLEXPWM0_ALL_PWM_SM_CLK_SOURCE_FREQ_HZ);

	FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_LDOK(kPWM_Control_Module_0);
	FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_RUN(kPWM_Control_Module_0);
	CTIMER_StartTimer(CTIMER1);

	while(pwm_busy_flag)
	{

	}

 	GPIO_PinWrite(EN_WHITE_GPIO, EN_WHITE_PIN, 0);
	GPIO_PinWrite(EN_YELLOW_GPIO, EN_YELLOW_PIN, 0);
	GPIO_PinWrite(EN_RED_GPIO, EN_RED_PIN, 0);
	GPIO_PinWrite(EN_GREEN_GPIO, EN_GREEN_PIN, 0);
	GPIO_PinWrite(EN_ORANGE_GPIO, EN_ORANGE_PIN, 0);
	GPIO_PinWrite(EN_BLUE_GPIO, EN_BLUE_PIN, 0);
}

void move_servo(uint8_t per)
{
	PWM_UpdatePwmDutycycle(FLEXPWM0_PERIPHERAL, FLEXPWM0_SERVO_PWM,
			kPWM_PwmB, kPWM_SignedCenterAligned, per);

	FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_LDOK(kPWM_Control_Module_1);
	FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_RUN(kPWM_Control_Module_1);

	for( uint8_t i=0; i<25; i++)
	{
		pwm_servo_busy_flag = true;
		CTIMER_StartTimer(CTIMER2);
		while(pwm_servo_busy_flag)
		{

		}
	}
}

void change_sides(uint8_t num)
{
	if(num <= 2)
	{
		move_motor(10,250);
		move_motor(6,250);
		move_motor(3,250);
		move_motor(11,250);
		move_motor(1,250);
		move_motor(8,250);
		move_motor(10,250);
		move_motor(6,250);
	}

	if((num >= 2) && (num < 5))
	{
		move_motor(12,250);
		move_motor(4,250);
		move_motor(5,250);
		move_motor(9,250);
		move_motor(1,250);
		move_motor(8,250);
		move_motor(12,250);
		move_motor(4,250);
	}

	if(num == 4)
	{
		move_motor(4,250);
		move_motor(12,250);
		move_motor(3,250);
		move_motor(3,250);
		move_motor(6,250);
		move_motor(6,250);
		move_motor(4,250);
		move_motor(4,250);
		move_motor(5,250);
		move_motor(5,250);
		move_motor(10,250);
		move_motor(6,250);
	}

	if(num == 5)
	{
		move_motor(6,250);
		move_motor(10,250);
		move_motor(5,250);
		move_motor(5,250);
		move_motor(4,250);
		move_motor(4,250);
		move_motor(6,250);
		move_motor(6,250);
		move_motor(3,250);
		move_motor(3,250);
		move_motor(4,250);
		move_motor(12,250);
	}
}
