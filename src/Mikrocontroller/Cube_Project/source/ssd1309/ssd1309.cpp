/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Cube_Project.h"
#include "ssd1309.h"
#include "peripherals.h"


// Send a byte to the command register
void ssd1309_WriteCommand(uint8_t byte)
{
    uint8_t buffer_tx[2] = {0x00,byte};

	LPI2C0_masterTransfer.slaveAddress = I2C_ADDR_SCREEN;
    LPI2C0_masterTransfer.flags = kLPI2C_TransferDefaultFlag;
    LPI2C0_masterTransfer.direction = kLPI2C_Write;
    LPI2C0_masterTransfer.dataSize = 2;
    LPI2C0_masterTransfer.data = buffer_tx;

    LPI2C_MasterTransferBlocking(LPI2C0, &LPI2C0_masterTransfer);
}

// Send data
void ssd1309_WriteData(uint8_t* buffer, size_t buff_size)
{
	uint8_t buffer_rx[buff_size+1];
	buffer_rx[0] = 0x40;

	for (int i=1; i<=(int)buff_size; i++)
	{
		buffer_rx[i] = buffer[i-1];
	}

	LPI2C0_masterTransfer.slaveAddress = I2C_ADDR_SCREEN;
    LPI2C0_masterTransfer.flags = kLPI2C_TransferDefaultFlag;
    LPI2C0_masterTransfer.direction = kLPI2C_Write;
    LPI2C0_masterTransfer.dataSize = buff_size+1;
    LPI2C0_masterTransfer.data = buffer_rx;

    LPI2C_MasterTransferBlocking(LPI2C0, &LPI2C0_masterTransfer);
}


/* Screenbuffer */
static uint8_t SSD1309_Buffer[SSD1309_BUFFER_SIZE];

/* Screen object */
static SSD1309_t SSD1309;


/* Fills the Screenbuffer with values from a given buffer of a fixed length */
SSD1309_Error_t ssd1309_FillBuffer(uint8_t *buf, uint32_t len)
{
    SSD1309_Error_t ret = SSD1309_ERR;

    if (len <= SSD1309_BUFFER_SIZE)
    {
        memcpy(SSD1309_Buffer, buf, len);
        ret = SSD1309_OK;
    }

    return ret;
}

void ssd1309_Init()
{
    /* Init OLED */
    ssd1309_WriteCommand(0xAE); /* Display off */

    ssd1309_WriteCommand(0x20); /* Set Memory Addressing Mode */
    ssd1309_WriteCommand(0x10); /* 00,Horizontal Addressing Mode; 01,Vertical Addressing Mode; */
                                /* 10,Page Addressing Mode (RESET); 11,Invalid */

    ssd1309_WriteCommand(0xB0); /*Set Page Start Address for Page Addressing Mode, 0-7 */

#ifdef SSD1309_MIRROR_VERT
    ssd1309_WriteCommand(0xC0); /* Mirror vertically */
#else
    ssd1309_WriteCommand(0xC8); /* Set COM Output Scan Direction */
#endif

    ssd1309_WriteCommand(0x00); /*---set low column address  */
    ssd1309_WriteCommand(0x10); /*---set high column address */

    ssd1309_WriteCommand(0x40); /*--set start line address - CHECK */

    ssd1309_WriteCommand(0x81); /*--set contrast control register - CHECK */
    ssd1309_WriteCommand(0xFF);

#ifdef SSD1309_MIRROR_HORIZ
    ssd1309_WriteCommand(0xA0); /* Mirror horizontally */
#else
    ssd1309_WriteCommand(0xA1); /* --set segment re-map 0 to 127 - CHECK */
#endif

#ifdef SSD1309_INVERSE_COLOR
    ssd1309_WriteCommand(0xA7); /*--set inverse color */
#else
    ssd1309_WriteCommand(0xA6); /*--set normal color */
#endif

/* Set multiplex ratio. */
#if (SSD1309_HEIGHT == 128)
    /* Found in the Luma Python lib for SH1106. */
    ssd1306_WriteCommand(0xFF);
#else
    ssd1309_WriteCommand(0xA8); /*--set multiplex ratio(1 to 64) - CHECK */
#endif

#if (SSD1309_HEIGHT == 32)
    ssd1309_WriteCommand(0x1F);
#elif (SSD1309_HEIGHT == 64)
    ssd1309_WriteCommand(0x3F);
#elif (SSD1309_HEIGHT == 128)
    ssd1309_WriteCommand(0x3F); /* Seems to work for 128px high displays too. */
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1309_WriteCommand(0xA4); /* 0xA4, Output follows RAM content;0xa5,Output ignores RAM content */

    ssd1309_WriteCommand(0xD3); /*-set display offset - CHECK */
    ssd1309_WriteCommand(0x00); /*-not offset */

    ssd1309_WriteCommand(0xD5); /*--set display clock divide ratio/oscillator frequency */
    ssd1309_WriteCommand(0xF0); /*--set divide ratio */

    ssd1309_WriteCommand(0xD9); /*--set pre-charge period */
    ssd1309_WriteCommand(0x22); /*			  */

    ssd1309_WriteCommand(0xDA); /*--set com pins hardware configuration - CHECK */
#if (SSD1309_HEIGHT == 32)
    ssd1309_WriteCommand(0x02);
#elif (SSD1309_HEIGHT == 64)
    ssd1309_WriteCommand(0x12);
#elif (SSD1309_HEIGHT == 128)
    ssd1309_WriteCommand(0x12);
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1309_WriteCommand(0xDB); /*--set vcomh */
    ssd1309_WriteCommand(0x20); /* 0x20, 0.77xVcc */

    ssd1309_WriteCommand(0x8D); /*--set DC-DC enable */
    ssd1309_WriteCommand(0x14); /*                   */
    ssd1309_WriteCommand(0xAF); /*--turn on SSD1309 panel */

    /* Clear screen */
    ssd1309_Fill(Black);

    /* Flush buffer to screen */
    ssd1309_UpdateScreen();

    /* Set default values for screen object */
    SSD1309.CurrentX = 0;
    SSD1309.CurrentY = 0;
    SSD1309.Rotation = ROTATION_0;

    SSD1309.Initialized = 1;
}


/* Fill the whole screen with the given color */
void ssd1309_Fill(SSD1309_COLOR color)
{
    /* Set memory */
    uint32_t i;

    for(i = 0; i < sizeof(SSD1309_Buffer); i++)
    {
        SSD1309_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
    }
}

/* Write the screenbuffer with changed to the screen */
void ssd1309_UpdateScreen(void)
{
    /* Write data to each page of RAM. Number of pages
     * depends on the screen height:
     *
     *  * 32px   ==  4 pages
     *  * 64px   ==  8 pages
     *  * 128px  ==  16 pages
     */
    for (uint8_t i = 0; i < (SSD1309_HEIGHT / 8); i++)
    {
        ssd1309_WriteCommand(0xB0 + i);
        ssd1309_WriteCommand(0x00 + SSD1309_X_OFFSET_LOWER);
        ssd1309_WriteCommand(0x10 + SSD1309_X_OFFSET_UPPER);
        ssd1309_WriteData(&SSD1309_Buffer[SSD1309_WIDTH * i], SSD1309_WIDTH);
    }
}

/*    Draw one pixel in the screenbuffer  */
/*    X => X Coordinate			  */
/*    Y => Y Coordinate			  */
/*    color => Pixel color		  */
void ssd1309_DrawPixel(uint8_t x, uint8_t y, SSD1309_COLOR color)
{
    if ((x >= SSD1309_WIDTH) || (y >= SSD1309_HEIGHT))
    {
        /* Don't write outside the buffer */
        return;
    }

    /* Draw in the right color */
    if (color == White)
    {
	    SSD1309_Buffer[x + (y / 8) * SSD1309_WIDTH] |= 1 << (y % 8);
    }
    else
    {
	    SSD1309_Buffer[x + (y / 8) * SSD1309_WIDTH] &= ~(1 << (y % 8));
    }
}

/* Draw 1 char to the screen buffer	      */
/* ch         => char om weg te schrijven     */
/* Font     => Font waarmee we gaan schrijven */
/* color     => Black or White                */
char ssd1309_WriteChar(char ch, FontDef Font, SSD1309_COLOR color)
{
    uint32_t i, b, j;

    /* Check if character is valid */
    if (ch < 32 || ch > 126)
    {
        return 0;
    }

    /* Check remaining space on current line */
    if ((SSD1309_WIDTH <= (SSD1309.CurrentX + Font.FontWidth))  ||
        (SSD1309_HEIGHT <= (SSD1309.CurrentY + Font.FontHeight))
       )
    {
        /* Not enough space on current line */
        return 0;
    }

    /* Use the font to write */
    for (i = 0; i < Font.FontHeight; i++)
    {
	b = Font.data[(ch - 32) * Font.FontHeight + i];

        for (j = 0; j < Font.FontWidth; j++)
	{
            if ((b << j) & 0x8000)
	    {
                ssd1309_DrawPixel(SSD1309.CurrentX + j, (SSD1309.CurrentY + i), (SSD1309_COLOR)color);
            }
	    else
	    {
                ssd1309_DrawPixel(SSD1309.CurrentX + j, (SSD1309.CurrentY + i), (SSD1309_COLOR)!color);
            }
        }
    }

    /* The current space is now taken */
    SSD1309.CurrentX += Font.FontWidth;

    /* Return written char for validation */
    return ch;
}


void ssd1309_WriteSymbol(SymbolID_t Symbol, uint8_t x, uint8_t y)
{
    uint32_t i, b, j;
    SSD1309_COLOR color = White;

    ssd1309_SetCursor(x, y);

    /* Check remaining space on current line */
    if ((SSD1309_WIDTH <= (SSD1309.CurrentX + SSD1309_Symbol[Symbol].SymbolWidth))  ||
        (SSD1309_HEIGHT <= (SSD1309.CurrentY + SSD1309_Symbol[Symbol].SymbolHeight))
       )
    {
        /* Not enough space on current line */
        return ;
    }

    /* Use the data to write */
    for (i = 0; i <= SSD1309_Symbol[Symbol].SymbolHeight; i++)
    {
	b = SSD1309_Symbol[Symbol].data[i];

        for (j = 0; j < SSD1309_Symbol[Symbol].SymbolWidth; j++)
	{
            if ((b << j) & 0x8000)
	    {
                ssd1309_DrawPixel(SSD1309.CurrentX + j, (SSD1309.CurrentY + i), (SSD1309_COLOR)color);
            }
	    else
	    {
                ssd1309_DrawPixel(SSD1309.CurrentX + j, (SSD1309.CurrentY + i), (SSD1309_COLOR)!color);
            }
        }
    }

    /* The current space is now taken */
    SSD1309.CurrentX += SSD1309_Symbol[Symbol].SymbolWidth;
}


/* Write full string to screenbuffer */
char ssd1309_WriteString(char* str, FontDef Font, SSD1309_COLOR color)
{
	while (*str) {
		if (ssd1309_WriteChar(*str, Font, color) != *str) {
			// Char could not be written
			return *str;
		}
		str++;
	}

	// Everything ok
	return *str;
}


/* Position the cursor */
void ssd1309_SetCursor(uint8_t x, uint8_t y)
{
    SSD1309.CurrentX = x - SSD1309_OFFSET_X;
    SSD1309.CurrentY = y - SSD1309_OFFSET_Y;
}

void ssd1309_SetContrast(const uint8_t value)
{
    const uint8_t kSetContrastControlRegister = 0x81;

    ssd1309_WriteCommand(kSetContrastControlRegister);
    ssd1309_WriteCommand(value);
}
