/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1309_CONF_H__
#define __SSD1309_CONF_H__

// Choose a bus
// #define SSD1309_USE_I2C
#define SSD1309_USE_SPI

// I2C Configuration
#if defined(SSD1309_USE_I2C)
#define SSD1309_I2C_ADDR        (0x3C)
#endif

// Include only needed fonts
#define SSD1309_INCLUDE_FONT_6x8
#define SSD1309_INCLUDE_FONT_7x10
#define SSD1309_INCLUDE_FONT_11x18
#define SSD1309_INCLUDE_FONT_16x26

// The width of the screen can be set using this
// define. The default value is 128.
// #define SSD1309_WIDTH           64

// If your screen horizontal axis does not start
// in column 0 you can use this define to
// adjust the horizontal offset
//#define SSD1309_OFFSET_X

// If your screen vertical axis does not start
// in column 0 you can use this define to
// adjust the vertical offset
//#define SSD1309_OFFSET_Y

// The height can be changed as well if necessary.
// It can be 32, 64 or 128. The default value is 64.
// #define SSD1309_HEIGHT          64

#endif /* __SSD1309_CONF_H__ */
