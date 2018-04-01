/**************************** Documentation ******************************/
/*
 * LCD16x2_Atmega16a.c
 *
 * Created: 29/03/2018 03:56:05 ص
 * Author : Amr Mostafa
 */ 

/**************************** PreProcessors ******************************/
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
/************************ Functions **************************/

int main(void)
{	
	LCD_Init();									// LCD initialization in 4-bits mode
	LCD_WriteString("Amr Mostafa");				// send this string
	_delay_ms(1000);							// delay 1s
	
	LCD_DisplayShift(RIGHT);					// shift the data present on LCD 1 step to right
	_delay_ms(1000);							// delay 1s
	LCD_DisplayShift(RIGHT);					// shift the data present on LCD 1 step to right
	_delay_ms(1000);							// delay 1s
	LCD_DisplayShift(RIGHT);					// shift the data present on LCD 1 step to right
	_delay_ms(1000);							// delay 1s
	
	LCD_DisplayShift(LEFT);						// shift the data present on LCD 1 step to left
	_delay_ms(1000);							// delay 1s
	LCD_DisplayShift(LEFT);						// shift the data present on LCD 1 step to left
	_delay_ms(1000);							// delay 1s
	LCD_DisplayShift(LEFT);						// shift the data present on LCD 1 step to left
	_delay_ms(1000);							// delay 1s
	
	LCD_CursorShift(RIGHT);						// shift cursor 1 step to right
	_delay_ms(1000);							// delay 1s
	LCD_CursorShift(RIGHT);						// shift cursor 1 step to right
	_delay_ms(1000);							// delay 1s
	LCD_CursorShift(RIGHT);						// shift cursor 1 step to right
	_delay_ms(1000);							// delay 1s
	
	LCD_CursorShift(LEFT);						// shift cursor 1 step to left
	_delay_ms(1000);							// delay 1s
	LCD_CursorShift(LEFT);						// shift cursor 1 step to left
	_delay_ms(1000);							// delay 1s
	LCD_CursorShift(LEFT);						// shift cursor 1 step to left
	_delay_ms(1000);							// delay 1s
	
	LCD_CursorMode(CURSOR_OFF);					// make cursor off
	_delay_ms(2000);							// delay 2s
	LCD_CursorMode(CURSOR_BLINK);				// make cursor blinking
	_delay_ms(2000);							// delay 2s
	LCD_CursorMode(CURSOR_ON);					// make cursor on
	_delay_ms(2000);							// delay 2s
	
	LCD_Line_Column(2 , 1);						// go to second line and first column
	_delay_ms(1000);							// delay 1s
	LCD_WriteString("Assalamu alaikum");		// send this string
	
    while (1)
    {
    }
}

