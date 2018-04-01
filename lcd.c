/************************ Documentaion **************************/
/*
 * lcd.c
 *
 * Created: 31/03/2018 11:35:43 ص
 *  Author: Amr Mostafa
 */ 

/************************ Preprocessors **************************/
#include "lcd.h"
#include <util/delay.h>
/************************ Functions Definitions **************************/

// function to send H-to-L enable pulse to LCD
// INPUT: ...
// OUTPUT: ...
// NOTES: minimum delay is 450ns, so 1us here is good
void LCD_Latch(void)
{
	EN_HIGH;				// make EN high
	_delay_us(1);			// delay 1us
	EN_LOW;					// make EN low
	_delay_us(1);			// delay 1us
}

// function to send command to LCD
// INPUT: cmd>command in 8bits
// OUTPUT: ...
// NOTES: using preprocessor #if here to allow user compile this code
//	if LCD D4-D7 are connected to micro controller port pins 4-7 OR pins 0-3
void LCD_WriteCMD(unsigned char cmd)
{
	ENABLE_WRITE_MODE;											// write mode R/W = 0
	ENABLE_CMD_REG;												// send command RS = 0
	#if (USE_MCU_PORT_HIGH_OR_LOW_NIBBLE == 0)					// compile for LCD D4-D7 connected to MCU port pins 0-3
	LCD_DATA_PORT = (cmd >> 4) | (LCD_DATA_PIN & 0xf0);			// send high 4bits to port without write to other port pins
	LCD_Latch();												// send H-to-L enable pulse to LCD
	LCD_DATA_PORT = (cmd & 0x0f) | (LCD_DATA_PIN & 0xf0);		// send low 4bits to port without write to other port pins
	LCD_Latch();												// send H-to-L enable pulse to LCD
	
	#elif (USE_MCU_PORT_HIGH_OR_LOW_NIBBLE == 1)				// compile for LCD D4-D7 connected to MCU port pins 4-7
	LCD_DATA_PORT = (cmd & 0xf0) | (LCD_DATA_PIN & 0x0f);		// send high 4bits to port without write to other port pins
	LCD_Latch();												// send H-to-L enable pulse to LCD
	LCD_DATA_PORT = (cmd << 4) | (LCD_DATA_PIN & 0x0f);			// send low 4bits to port without write to other port pins
	LCD_Latch();												// send H-to-L enable pulse to LCD
	#endif
	
	if (cmd == 0x01 || cmd == 0x02)
	{
		// these 2 commands need delay of minimum 1.64ms, so 2ms is good enough
		_delay_ms(2);
	}
	else
	{
		// all other commands need delay of minimum 40us, so 100us is good enough
		_delay_us(100);
	}
}

// function to send command to LCD
// INPUT: data>ascii character in 8bits
// OUTPUT: ...
// NOTES: using preprocessor #if here to allow user compile this code
//	if LCD D4-D7 are connected to micro controller port pins 4-7 OR pins 0-3
void LCD_WriteData(unsigned char data)
{
	ENABLE_WRITE_MODE;												// write mode R/W = 0
	ENABLE_DATA_REG;												// send data RS = 1
	#if (USE_MCU_PORT_HIGH_OR_LOW_NIBBLE == 0)						// compile for LCD D4-D7 connected to MCU port pins 0-3
	LCD_DATA_PORT = (data >> 4) | (LCD_DATA_PIN & 0xf0);									// send high 4bits to port without write to other port pins
	LCD_Latch();													// send H-to-L enable pulse to LCD
	LCD_DATA_PORT = (data & 0x0f) | (LCD_DATA_PIN & 0xf0);									// send low 4bits to port without write to other port pins
	LCD_Latch();													// send H-to-L enable pulse to LCD
	
	#elif (USE_MCU_PORT_HIGH_OR_LOW_NIBBLE == 1)					// compile for LCD D4-D7 connected to MCU port pins 4-7
	LCD_DATA_PORT = (data & 0xf0) | (LCD_DATA_PIN & 0x0f);			// send high 4bits to port without write to other port pins
	LCD_Latch();													// send H-to-L enable pulse to LCD
	LCD_DATA_PORT = (data << 4) | (LCD_DATA_PIN & 0x0f);			// send low 4bits to port without write to other port pins
	LCD_Latch();													// send H-to-L enable pulse to LCD
	#endif
	_delay_us(100);													// delay 100us for data to be processed by LCD before sending any other data
}

// function to send string to LCD
// INPUT: pointer to the first element of the character array
// OUTPUT: ...
// NOTES: ...
void LCD_WriteString(char *str)
{
	// loop until pointer dereference = '\0'
	while(*str)
	{
		LCD_WriteData(*str);				// send current array character to the LCD
		str++;								// point to the next character address
	}
}

// function to clear the LCD
// INPUT: ...
// OUTPUT: ...
// NOTES: ...
void LCD_Clear(void)
{
	LCD_WriteCMD(0x01);						// send clear command to the LCD
}

// function to select cursor mode
// INPUT: mode> 3 modes available as follow:
//				CURSOR_ON: cursor is on and stable (no blinking)
//				CURSOR_BLINK: cursor is on and blinking
//				CURSOR_OFF: cursor is off (disappears)
// OUTPUT: ...
// NOTES: ...
void LCD_CursorMode(unsigned char mode)
{
	if (mode == CURSOR_ON)
	{
		LCD_WriteCMD(0x0e);				// display on .. cursor on .. blinking off
	}
	else if (mode == CURSOR_BLINK)
	{
		LCD_WriteCMD(0x0f);				// display on .. cursor on .. blinking on
	}
	else if (mode == CURSOR_OFF)
	{
		LCD_WriteCMD(0x0c);				// display on .. cursor off
	}
}

// function to shift cursor 1 step right OR left
// INPUT: direction> 2 directions available as follow:
//				RIGHT: shift cursor 1 step to right
//				LEFT: shift cursor 1 step to left
// OUTPUT: ...
// NOTES: ...
void LCD_CursorShift(unsigned char direction)
{
	if (direction == RIGHT)
	{
		LCD_WriteCMD(0x14);				// shift cursor 1 step to right
	}
	else if (direction == LEFT)
	{
		LCD_WriteCMD(0x10);				// shift cursor 1 step to left
	}
}

// function to shift data on LCD 1 step right OR left
// INPUT: direction> 2 directions available as follow:
//				RIGHT: shift data on LCD 1 step to right
//				LEFT: shift data on LCD 1 step to left
// OUTPUT: ...
// NOTES: ...
void LCD_DisplayShift(unsigned char direction)
{
	if (direction == RIGHT)
	{
		LCD_WriteCMD(0x1c);				// shift data on LCD 1 step to right
	}
	else if (direction == LEFT)
	{
		LCD_WriteCMD(0x18);				// shift data on LCD 1 step to left
	}
}

// function to move LCD AC(address counter of the LCD DDRAM) to a certain position
// INPUT: line> allowed values are: 1 to move AC to the first horizontal line
//									2 to move AC to the second horizontal line
//		  column> allowed values are from 1:16 to move the AC to any position
// OUTPUT: ...
// NOTES: any values other than 1 OR 2 for line .. 1-16 for column will be ignored
void LCD_Line_Column(unsigned char line , unsigned char column)
{
	if (line == 1 && column >= 1 && column <= 16)
	{
		LCD_WriteCMD( 0x80 | (0x00 +     column - 1 ) );			// move AC to line 1 , column's position
	}
	else if (line == 2 && column >= 1 && column <= 16)
	{
		LCD_WriteCMD( 0x80 | (0x40 +     column - 1 ) );			// move AC to line 2 , column's position
	}
}

// function to initialize the 16x2 LCD in 4-bits mode and also initialize micro controller port pins
// INPUT: ...
// OUTPUT: ...
// NOTES: ...
void LCD_Init(void)
{
	LCD_CONTROL_DDR |=1<<RS | 1<<RW | 1<<EN;											// all 3 control pins are output
	LCD_DATA_DDR |= 1<<LCD_D4_PIN | 1<<LCD_D5_PIN | 1<<LCD_D6_PIN | 1<<LCD_D7_PIN;		// all 4 data/command pins are output
	_delay_ms(20);						// wait minimum of 15ms for LCD, so 20ms is good enough
	LCD_WriteCMD(0x33);					// 4 bit sequence for LCD 4-bits initializing
	LCD_WriteCMD(0x32);					// 4 bit sequence for LCD 4-bits initializing
	LCD_WriteCMD(0x28);					// mode:4 bit , display:2Lines , font:5x7 dots
	LCD_WriteCMD(0x0e);					// display on .. cursor on .. blinking off
	LCD_Clear();						// clear LCD , set LCD cursor to 0 (display address counter = 0)
}