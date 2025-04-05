/*
*   Gerrit Hinrichs 01.2025
*   github.com/snech99
*
*   Cube_Solver_Robot
*   main file for the Controller with super-loop
*/
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "clock_config.h"
#include "MCXA153.h"

#include "Cube_Project.h"
#include "state_machine.h"

uint8_t rx_buffer[BUFFER_MAX] = {};
uint16_t rx_buffer_index = 0;

bool flag_hit_1 = false;
bool flag_hit_2 = false;
bool SW_hit_flag = false;
bool SW_flag_TL = false;
bool SW_flag_TR = false;
bool SW_flag_BL = false;
bool SW_flag_BR = false;
bool color_busy_flag = true;
bool pwm_busy_flag = false;
bool pwm_servo_busy_flag = false;
bool NULL_flag = false;

uint32_t tick_count = 0;
uint32_t tick_start = 0;
uint32_t tick_end = 0;

volatile uint32_t pwm_ms_count = 0;
volatile int32_t PWM_flanke_count = 250;
volatile uint32_t PWM_frequenz = PWM_FREQUENZ;
volatile uint32_t PWM_ramp_time = RAMP_LONG;

// Timer for PWM-Ramp
void TIMER1_CALLBACK_RAMPE(uint32_t flags)
{
	if (pwm_ms_count < (PWM_ramp_time-1))
	{
		float add_frequenz = (float)PWM_frequenz/PWM_ramp_time;
		uint32_t new_frequenz = (uint32_t) add_frequenz + (pwm_ms_count*add_frequenz);

		if(new_frequenz == 0)
		{
			new_frequenz = 1;
		}
		pwm_ms_count++;

		PWM_SetupPwm(FLEXPWM0_PERIPHERAL, FLEXPWM0_ALL_PWM, FLEXPWM0_ALL_PWM_pwm_function_config, 1U, kPWM_SignedCenterAligned,
				new_frequenz, FLEXPWM0_ALL_PWM_SM_CLK_SOURCE_FREQ_HZ);

		FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_LDOK(kPWM_Control_Module_0);
	}
	else
	{
		if(PWM_frequenz == 0)
		{
			PWM_frequenz = 1;
		}

		PWM_SetupPwm(FLEXPWM0_PERIPHERAL, FLEXPWM0_ALL_PWM, FLEXPWM0_ALL_PWM_pwm_function_config, 1U, kPWM_SignedCenterAligned,
				PWM_frequenz, FLEXPWM0_ALL_PWM_SM_CLK_SOURCE_FREQ_HZ);


		FLEXPWM0_PERIPHERAL->MCTRL |= PWM_MCTRL_LDOK(kPWM_Control_Module_0);
		CTIMER_StopTimer(CTIMER1);
	}
}

// Timer to debounce the buttons
void TIMER0_ISR_RESET_CALLBACK(uint32_t flags)
{
	if(GPIO_PinRead(GPIO2, TASTER_T_L) == 0)
	{
		SW_flag_TL = true;
	}

	if(GPIO_PinRead(GPIO2, TASTER_T_R) == 0)
	{
		SW_flag_TR = true;
	}

	if(GPIO_PinRead(GPIO2, TASTER_B_L) == 0)
	{
		SW_flag_BL = true;
	}

	if(GPIO_PinRead(GPIO2, TASTER_B_R) == 0)
	{
		SW_flag_BR = true;
	}

	GPIO_GpioClearInterruptFlags(GPIO2, 1<<TASTER_T_L);
	GPIO_GpioClearInterruptFlags(GPIO2, 1<<TASTER_T_R);
	GPIO_GpioClearInterruptFlags(GPIO2, 1<<TASTER_B_L);
	GPIO_GpioClearInterruptFlags(GPIO2, 1<<TASTER_B_R);

	CTIMER_StopTimer(CTIMER0);
	EnableIRQ(GPIO2_IRQN);
}

// General delay Timer
void Busy_Timer(uint32_t flags)
{
	pwm_servo_busy_flag = false;
	pwm_busy_flag = false;
}

/* FLEXPWM0_SUBMODULE0_IRQn interrupt handler */
extern "C" void INTERRUPT_PWM(void)
{
	if (PWM_GetStatusFlags(FLEXPWM0_PERIPHERAL, kPWM_Module_0) & kPWM_CompareVal2Flag)
	{
		PWM_flanke_count--;
		if(PWM_flanke_count <= 0)
		{
			FLEXPWM0_PERIPHERAL->MCTRL &= ~(PWM_MCTRL_RUN(kPWM_Control_Module_0));
			CTIMER_StartTimer(CTIMER2);
		}
	}
	PWM_ClearStatusFlags(FLEXPWM0_PERIPHERAL, kPWM_Module_0, kPWM_CompareVal2Flag);
}


/* LPUART0_IRQn interrupt handler */
extern "C" void LPUART2_SERIAL_RX_TX_IRQHANDLER(void)
{
	uint8_t data;
	uint32_t status= LPUART_GetStatusFlags(LPUART2_PERIPHERAL);

	if ( (status & kLPUART_RxDataRegFullFlag) )
	{
		data = LPUART_ReadByte(LPUART2_PERIPHERAL);

		if(rx_buffer_index < BUFFER_MAX)
		{
			rx_buffer[rx_buffer_index] = data;
			rx_buffer_index ++;
		}
		else
		{
			GPIO_PinWrite(BOARD_LED_RED_GPIO, 12, 0);
			GPIO_PinWrite(BOARD_LED_GREEN_GPIO, 13, 1);
			GPIO_PinWrite(BOARD_LED_BLUE_GPIO, 0, 0);
		}

		if(data == '$')
		{
			flag_hit_1 = true;
		}

		if((data == '%') && flag_hit_1)
		{
			flag_hit_2 = true;
		}
	}
	LPUART_ClearStatusFlags(LPUART2_PERIPHERAL, kLPUART_RxDataRegFullFlag);
}

/* GPIO1_IRQn interrupt handler */
extern "C" void GPIO1_IRQHANDLER(void)
{
	uint32_t hit_flag = GPIO_GpioGetInterruptFlags(GPIO1);

	if((hit_flag>>INTERUPT_SENSOR_PIN) == 1)
	{
		color_busy_flag = false;
	}

	GPIO_GpioClearInterruptFlags(GPIO1, 1<<INTERUPT_SENSOR_PIN);
}

// IRQN for the Buttons
extern "C" void GPIO2_IRQHANDLER(void)
{
	uint32_t hit_flag = GPIO_GpioGetInterruptFlags(GPIO2);

	if((hit_flag>>TASTER_T_L) == 1)
	{
		DisableIRQ(GPIO2_IRQN);
		CTIMER_StartTimer(CTIMER0);
	}

	if((hit_flag>>TASTER_T_R) == 1)
	{
		DisableIRQ(GPIO2_IRQN);
		CTIMER_StartTimer(CTIMER0);
	}

	if((hit_flag>>TASTER_B_L) == 1)
	{
		DisableIRQ(GPIO2_IRQN);
		CTIMER_StartTimer(CTIMER0);
	}

	if((hit_flag>>TASTER_B_R) == 1)
	{
		DisableIRQ(GPIO2_IRQN);
		CTIMER_StartTimer(CTIMER0);
	}

	GPIO_GpioClearInterruptFlags(GPIO2, 1<<TASTER_T_L);
	GPIO_GpioClearInterruptFlags(GPIO2, 1<<TASTER_T_R);
	GPIO_GpioClearInterruptFlags(GPIO2, 1<<TASTER_B_L);
	GPIO_GpioClearInterruptFlags(GPIO2, 1<<TASTER_B_R);
}

/* GPIO3_IRQn interrupt handler */
extern "C" void GPIO3_IRQHANDLER(void)
{
	uint32_t hit_flag = GPIO_GpioGetInterruptFlags(GPIO3);

	if((hit_flag>>NULL_TRIGGER_PIN) == 1)
	{
		NULL_flag = true;
	}
	GPIO_GpioClearInterruptFlags(NULL_TRIGGER_GPIO, 1<<NULL_TRIGGER_PIN);
}

// returns a "random" number
uint8_t get_rand_num()
{
    srand(SysTick->VAL%65535);
    return (rand()%12 + 1);
}

// Interrupt for SysTick
extern "C" void SysTick_Handler(void)
{
	tick_count++;
}

// Calculates the time needed for a specific function
uint32_t calc_time_ms()
{
	uint32_t erg = 0;
	if (tick_end >= tick_start)
	{
		erg = tick_end - tick_start;
	}
	else
	{
		erg = (0xFFFFFFFF - tick_start) + tick_end;
	}
	return erg;
}


/*
 * @brief   Application entry point.
 */
int main(void)
{
	char buf_1[] = "Automatic (intern)";
	char buf_2[] = "external_PC USB";
	char buf_e[] = "err in Sensor-Config";

	uint32_t time = 0;

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    SysTick_Config(SystemCoreClock/1000);

    GPIO_PinWrite(MOTOR_EN_GPIO, MOTOR_EN_PIN, M_ENABLE);

#ifdef STEINBRECHER
    tick_start = tick_count;
    while(time < 2000)
    {
    	tick_end = tick_count;
    	time = calc_time_ms();
    }
#endif

	config_motor();

    ssd1309_Init();
    ssd1309_Fill(Black);
    ssd1309_UpdateScreen();

    if (!tcs.init())
    {
    	ssd1309_SetCursor(2,3);
    	ssd1309_WriteString(buf_e,Font_7x10, White);
    }
    else
    {
    	ssd1309_SetCursor(2,3);
    	ssd1309_WriteString(buf_1,Font_7x10, White);
    	ssd1309_SetCursor(2,50);
    	ssd1309_WriteString(buf_2,Font_7x10, White);
    }
    ssd1309_UpdateScreen();

    tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE);
    tcs.setInterrupt(true);

#ifdef STEINBRECHER
    SW_flag_TL = true;
#endif

	while(true)
	{
		// State-Machine
		super_machine();
	}
    return 0 ;
}
