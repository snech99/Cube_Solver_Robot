/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define PCR_IBE_ibe1 0x01u /*!<@brief Input Buffer Enable: Enables */
#define PCR_PE_pe1 0x01u   /*!<@brief Pull Enable: Enables */
#define PCR_PS_ps1 0x01u   /*!<@brief Pull Select: Enables internal pullup resistor */

/*! @name PORT1_4 (number 62), UART_RX
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITCOM_UART_RX_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITCOM_UART_RX_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_INITCOM_UART_RX_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT1_5 (number 63), UART_TX
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITCOM_UART_TX_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITCOM_UART_TX_PIN 5U                   /*!<@brief PORT pin number */
#define BOARD_INITCOM_UART_TX_PIN_MASK (1U << 5U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT1_9 (number 3), I2C_SCL
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITCOM_I2C_SCL_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITCOM_I2C_SCL_PIN 9U                   /*!<@brief PORT pin number */
#define BOARD_INITCOM_I2C_SCL_PIN_MASK (1U << 9U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT1_8 (number 2), I2C_SDA
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITCOM_I2C_SDA_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITCOM_I2C_SDA_PIN 8U                   /*!<@brief PORT pin number */
#define BOARD_INITCOM_I2C_SDA_PIN_MASK (1U << 8U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitCOM(void);

/*! @name PORT3_12 (number 38), LED_RED
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITLED_LED_RED_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITLED_LED_RED_GPIO_PIN 12U              /*!<@brief GPIO pin number */
#define BOARD_INITLED_LED_RED_GPIO_PIN_MASK (1U << 12U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITLED_LED_RED_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITLED_LED_RED_PIN 12U                   /*!<@brief PORT pin number */
#define BOARD_INITLED_LED_RED_PIN_MASK (1U << 12U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_13 (number 37), LED_GREEN
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITLED_LED_GREEN_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITLED_LED_GREEN_GPIO_PIN 13U              /*!<@brief GPIO pin number */
#define BOARD_INITLED_LED_GREEN_GPIO_PIN_MASK (1U << 13U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITLED_LED_GREEN_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITLED_LED_GREEN_PIN 13U                   /*!<@brief PORT pin number */
#define BOARD_INITLED_LED_GREEN_PIN_MASK (1U << 13U)      /*!<@brief PORT pin mask */
                                                          /* @} */

/*! @name PORT3_0 (number 46), PWM
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITLED_LED_BLUE_GPIO GPIO3               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITLED_LED_BLUE_GPIO_PIN 0U              /*!<@brief GPIO pin number */
#define BOARD_INITLED_LED_BLUE_GPIO_PIN_MASK (1U << 0U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITLED_LED_BLUE_PORT PORT3               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITLED_LED_BLUE_PIN 0U                   /*!<@brief PORT pin number */
#define BOARD_INITLED_LED_BLUE_PIN_MASK (1U << 0U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLED(void);

#define PCR_IBE_ibe1 0x01u          /*!<@brief Input Buffer Enable: Enables */
#define PCR_PE_pe1 0x01u            /*!<@brief Pull Enable: Enables */
#define PCR_PS_ps1 0x01u            /*!<@brief Pull Select: Enables internal pullup resistor */
#define PORT2_PCR13_MUX_mux00 0x00u /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR16_MUX_mux00 0x00u /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR1_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR2_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR6_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */

/*! @name PORT1_7 (number 1), SW_3
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITSW_SW_3_GPIO GPIO1               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITSW_SW_3_GPIO_PIN 7U              /*!<@brief GPIO pin number */
#define BOARD_INITSW_SW_3_GPIO_PIN_MASK (1U << 7U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITSW_SW_3_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITSW_SW_3_PIN 7U                   /*!<@brief PORT pin number */
#define BOARD_INITSW_SW_3_PIN_MASK (1U << 7U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORT2_6 (number 20), TASTER_T_L
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITSW_TASTER_T_L_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITSW_TASTER_T_L_GPIO_PIN 6U              /*!<@brief GPIO pin number */
#define BOARD_INITSW_TASTER_T_L_GPIO_PIN_MASK (1U << 6U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITSW_TASTER_T_L_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITSW_TASTER_T_L_PIN 6U                   /*!<@brief PORT pin number */
#define BOARD_INITSW_TASTER_T_L_PIN_MASK (1U << 6U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT2_13 (number 23), TASTER_B_L
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITSW_TASTER_B_L_GPIO GPIO2                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITSW_TASTER_B_L_GPIO_PIN 13U              /*!<@brief GPIO pin number */
#define BOARD_INITSW_TASTER_B_L_GPIO_PIN_MASK (1U << 13U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITSW_TASTER_B_L_PORT PORT2                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITSW_TASTER_B_L_PIN 13U                   /*!<@brief PORT pin number */
#define BOARD_INITSW_TASTER_B_L_PIN_MASK (1U << 13U)      /*!<@brief PORT pin mask */
                                                          /* @} */

/*! @name PORT2_2 (number 16), TASTER_B_R
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITSW_TASTER_B_R_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITSW_TASTER_B_R_GPIO_PIN 2U              /*!<@brief GPIO pin number */
#define BOARD_INITSW_TASTER_B_R_GPIO_PIN_MASK (1U << 2U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITSW_TASTER_B_R_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITSW_TASTER_B_R_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_INITSW_TASTER_B_R_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT2_16 (number 24), TASTER_T_R
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITSW_TASTER_T_R_GPIO GPIO2                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITSW_TASTER_T_R_GPIO_PIN 16U              /*!<@brief GPIO pin number */
#define BOARD_INITSW_TASTER_T_R_GPIO_PIN_MASK (1U << 16U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITSW_TASTER_T_R_PORT PORT2                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITSW_TASTER_T_R_PIN 16U                   /*!<@brief PORT pin number */
#define BOARD_INITSW_TASTER_T_R_PIN_MASK (1U << 16U)      /*!<@brief PORT pin mask */
                                                          /* @} */

/*! @name PORT2_1 (number 15), LED_SWITCH
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITSW_LED_SWITCH_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITSW_LED_SWITCH_GPIO_PIN 1U              /*!<@brief GPIO pin number */
#define BOARD_INITSW_LED_SWITCH_GPIO_PIN_MASK (1U << 1U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITSW_LED_SWITCH_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITSW_LED_SWITCH_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_INITSW_LED_SWITCH_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT1_6 (number 64), INTERUPT_SENSOR
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITSW_INTERUPT_SENSOR_GPIO GPIO1               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITSW_INTERUPT_SENSOR_GPIO_PIN 6U              /*!<@brief GPIO pin number */
#define BOARD_INITSW_INTERUPT_SENSOR_GPIO_PIN_MASK (1U << 6U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITSW_INTERUPT_SENSOR_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITSW_INTERUPT_SENSOR_PIN 6U                   /*!<@brief PORT pin number */
#define BOARD_INITSW_INTERUPT_SENSOR_PIN_MASK (1U << 6U)      /*!<@brief PORT pin mask */
                                                              /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSW(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitCLOCK(void);

/*! @name PORT3_30 (number 31), DIR_blue
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_DIR_blue_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_DIR_blue_GPIO_PIN 30U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_DIR_blue_GPIO_PIN_MASK (1U << 30U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_DIR_blue_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_DIR_blue_PIN 30U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_DIR_blue_PIN_MASK (1U << 30U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT2_0 (number 14), DIR_green
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_DIR_green_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_DIR_green_GPIO_PIN 0U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_DIR_green_GPIO_PIN_MASK (1U << 0U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_DIR_green_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_DIR_green_PIN 0U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_DIR_green_PIN_MASK (1U << 0U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT1_13 (number 7), DIR_yellow
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_DIR_yellow_GPIO GPIO1                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_DIR_yellow_GPIO_PIN 13U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_DIR_yellow_GPIO_PIN_MASK (1U << 13U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_DIR_yellow_PORT PORT1                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_DIR_yellow_PIN 13U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_DIR_yellow_PIN_MASK (1U << 13U)      /*!<@brief PORT pin mask */
                                                           /* @} */

/*! @name PORT1_12 (number 6), DIR_white
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_DIR_white_GPIO GPIO1                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_DIR_white_GPIO_PIN 12U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_DIR_white_GPIO_PIN_MASK (1U << 12U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_DIR_white_PORT PORT1                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_DIR_white_PIN 12U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_DIR_white_PIN_MASK (1U << 12U)      /*!<@brief PORT pin mask */
                                                          /* @} */

/*! @name PORT3_1 (number 45), EN_GREEN
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_EN_GREEN_GPIO GPIO3               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_EN_GREEN_GPIO_PIN 1U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_EN_GREEN_GPIO_PIN_MASK (1U << 1U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_EN_GREEN_PORT PORT3               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_EN_GREEN_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_EN_GREEN_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT2_5 (number 19), EN_RED
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_EN_RED_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_EN_RED_GPIO_PIN 5U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_EN_RED_GPIO_PIN_MASK (1U << 5U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_EN_RED_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_EN_RED_PIN 5U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_EN_RED_PIN_MASK (1U << 5U)      /*!<@brief PORT pin mask */
                                                      /* @} */

/*! @name PORT2_4 (number 18), EN_YELLOW
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_EN_YELLOW_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_EN_YELLOW_GPIO_PIN 4U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_EN_YELLOW_GPIO_PIN_MASK (1U << 4U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_EN_YELLOW_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_EN_YELLOW_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_EN_YELLOW_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT3_14 (number 36), EN_BLUE
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_EN_BLUE_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_EN_BLUE_GPIO_PIN 14U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_EN_BLUE_GPIO_PIN_MASK (1U << 14U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_EN_BLUE_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_EN_BLUE_PIN 14U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_EN_BLUE_PIN_MASK (1U << 14U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_15 (number 35), EN_ORANGE
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_EN_ORANGE_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_EN_ORANGE_GPIO_PIN 15U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_EN_ORANGE_GPIO_PIN_MASK (1U << 15U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_EN_ORANGE_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_EN_ORANGE_PIN 15U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_EN_ORANGE_PIN_MASK (1U << 15U)      /*!<@brief PORT pin mask */
                                                          /* @} */

/*! @name PORT2_3 (number 17), EN_WHITE
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_EN_WHITE_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_EN_WHITE_GPIO_PIN 3U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_EN_WHITE_GPIO_PIN_MASK (1U << 3U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_EN_WHITE_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_EN_WHITE_PIN 3U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_EN_WHITE_PIN_MASK (1U << 3U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_8 (number 42), NULL_TRIGGER
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_NULL_TRIGGER_GPIO GPIO3               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_NULL_TRIGGER_GPIO_PIN 8U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_NULL_TRIGGER_GPIO_PIN_MASK (1U << 8U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_NULL_TRIGGER_PORT PORT3               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_NULL_TRIGGER_PIN 8U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_NULL_TRIGGER_PIN_MASK (1U << 8U)      /*!<@brief PORT pin mask */
                                                            /* @} */

/*! @name PORT3_29 (number 32), DIR_orange
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_DIR_orange_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_DIR_orange_GPIO_PIN 29U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_DIR_orange_GPIO_PIN_MASK (1U << 29U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_DIR_orange_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_DIR_orange_PIN 29U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_DIR_orange_PIN_MASK (1U << 29U)      /*!<@brief PORT pin mask */
                                                           /* @} */

/*! @name PORT3_31 (number 30), DIR_red
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_DIR_red_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_DIR_red_GPIO_PIN 31U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_DIR_red_GPIO_PIN_MASK (1U << 31U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_DIR_red_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_DIR_red_PIN 31U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_DIR_red_PIN_MASK (1U << 31U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_9 (number 41), SERVO_PWM
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_SERVO_PWM_PORT PORT3               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_SERVO_PWM_PIN 9U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_SERVO_PWM_PIN_MASK (1U << 9U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT3_6 (number 44), PWM_ALL
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_PWM_ALL_PORT PORT3               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_PWM_ALL_PIN 6U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_PWM_ALL_PIN_MASK (1U << 6U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT2_7 (number 21), MOTOR_ALL_EN
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPWM_MOTOR_ALL_EN_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPWM_MOTOR_ALL_EN_GPIO_PIN 7U              /*!<@brief GPIO pin number */
#define BOARD_INITPWM_MOTOR_ALL_EN_GPIO_PIN_MASK (1U << 7U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPWM_MOTOR_ALL_EN_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPWM_MOTOR_ALL_EN_PIN 7U                   /*!<@brief PORT pin number */
#define BOARD_INITPWM_MOTOR_ALL_EN_PIN_MASK (1U << 7U)      /*!<@brief PORT pin mask */
                                                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPWM(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
