/**************************** Documentation ******************************/
/*
 * lcd.h
 *
 * Created: 31/03/2018 11:35:54 ص
 *  Author: Amr Mostafa
 */ 

/**************************** PreProcessors ******************************/
#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU						// if CPU clock not defined
#define F_CPU	16000000UL			// then define it as  16MHZ
#endif

#include <avr/io.h>

#define LCD_DATA_DDR		DDRA						// LCD data/command port direction register		
#define LCD_DATA_PORT		PORTA						// LCD data/command port register
#define LCD_DATA_PIN		PINA						// LCD data/command pin register	
#define LCD_CONTROL_DDR		DDRB						// LCD control port direction register	
#define LCD_CONTROL_PORT	PORTB						// LCD control port register	
#define USE_MCU_PORT_HIGH_OR_LOW_NIBBLE			0		// 0>use port 0,1,2,3 pins .. 1>use port 4,5,6,7 pins
#define LCD_D4_PIN								0		// make it 0 if USE_MCU_PORT_HIGH_OR_LOW_NIBBLE = 0 .. 4 if USE_MCU_PORT_HIGH_OR_LOW_NIBBLE = 1
#define LCD_D5_PIN								1		// make it 1 if USE_MCU_PORT_HIGH_OR_LOW_NIBBLE = 0 .. 5 if USE_MCU_PORT_HIGH_OR_LOW_NIBBLE = 1
#define LCD_D6_PIN								2		// make it 2 if USE_MCU_PORT_HIGH_OR_LOW_NIBBLE = 0 .. 6 if USE_MCU_PORT_HIGH_OR_LOW_NIBBLE = 1
#define LCD_D7_PIN								3		// make it 3 if USE_MCU_PORT_HIGH_OR_LOW_NIBBLE = 0 .. 7 if USE_MCU_PORT_HIGH_OR_LOW_NIBBLE = 1
#define RS										0		// LCD RS pin
#define RW										1		// LCD R/W pin
#define EN										2		// LCD EN pin
#define ENABLE_READ_MODE						(LCD_CONTROL_PORT |=1<<RW)			// read mode enable R/W = 1
#define ENABLE_WRITE_MODE						(LCD_CONTROL_PORT &=~(1<<RW))		// write mode enable R/W = 0
#define ENABLE_DATA_REG							(LCD_CONTROL_PORT |=1<<RS)			// data sending enable RS = 1
#define ENABLE_CMD_REG							(LCD_CONTROL_PORT &=~(1<<RS))		// command sending enable RS = 0
#define EN_HIGH									(LCD_CONTROL_PORT |=1<<EN)			// make EN high
#define EN_LOW									(LCD_CONTROL_PORT &=~(1<<EN))		// make EN low
#define CURSOR_ON								0		// just indicator number make cursor on
#define CURSOR_BLINK							1		// just indicator number make cursor blink
#define CURSOR_OFF								2		// just indicator number make cursor off
#define RIGHT									0		// just indicator number make cursor/display shift right
#define LEFT									1		// just indicator number make cursor/display shift left

/******************* Prototypes and Global variables *********************/
// function to send H-to-L enable pulse to LCD
// INPUT: ...
// OUTPUT: ...
// NOTES: minimum delay is 450ns, so 1us here is good
void LCD_Latch(void);

// function to send command to LCD
// INPUT: cmd>command in 8bits
// OUTPUT: ...
// NOTES: using preprocessor #if here to allow user compile this code
//	if LCD D4-D7 are connected to micro controller port pins 4-7 OR pins 0-3
void LCD_WriteCMD(unsigned char cmd);

// function to send command to LCD
// INPUT: data>ascii character in 8bits
// OUTPUT: ...
// NOTES: using preprocessor #if here to allow user compile this code
//	if LCD D4-D7 are connected to micro controller port pins 4-7 OR pins 0-3
void LCD_WriteData(unsigned char data);

// function to send string to LCD
// INPUT: pointer to the first element of the character array
// OUTPUT: ...
// NOTES: ...
void LCD_WriteString(char *str);

// function to clear the LCD
// INPUT: ...
// OUTPUT: ...
// NOTES: ...
void LCD_Clear(void);

// function to select cursor mode
// INPUT: mode> 3 modes available as follow:
//				CURSOR_ON: cursor is on and stable (no blinking)
//				CURSOR_BLINK: cursor is on and blinking
//				CURSOR_OFF: cursor is off (disappears)
// OUTPUT: ...
// NOTES: ...

void LCD_CursorMode(unsigned char mode);

// function to shift cursor 1 step right OR left
// INPUT: direction> 2 directions available as follow:
//				RIGHT: shift cursor 1 step to right
//				LEFT: shift cursor 1 step to left
// OUTPUT: ...
// NOTES: ...
void LCD_CursorShift(unsigned char direction);

// function to shift data on LCD 1 step right OR left
// INPUT: direction> 2 directions available as follow:
//				RIGHT: shift data on LCD 1 step to right
//				LEFT: shift data on LCD 1 step to left
// OUTPUT: ...
// NOTES: ...
void LCD_DisplayShift(unsigned char direction);

// function to move LCD AC(address counter of the LCD DDRAM) to a certain position
// INPUT: line> allowed values are: 1 to move AC to the first horizontal line
//									2 to move AC to the second horizontal line
//		  column> allowed values are from 1:16 to move the AC to any position
// OUTPUT: ...
// NOTES: any values other than 1 OR 2 for line .. 1-16 for column will be ignored
void LCD_Line_Column(unsigned char line , unsigned char column);

// function to initialize the 16x2 LCD in 4-bits mode and also initialize micro controller port pins
// INPUT: ...
// OUTPUT: ...
// NOTES: ...
void LCD_Init(void);

#endif /* LCD_H_ */