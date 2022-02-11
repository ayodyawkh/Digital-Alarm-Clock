/*
 * lcd.h
 *
 * Created: 6/21/2021 10:03:18 PM
 *  Author: USER
 */ 


#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LCD_DIRECTORY  DDRD	/*Define LCD port*/
#define LCD_Port PORTD		/* Define LCD data port */
#define RS PORTD0	        /* Define Register Select pin */
#define EN PORTD1			/* Define Enable Signal pin */

void sendCommand( unsigned char command );
void sendCharacter( unsigned char data );
void initializeLCD (void);
void sendString (char *str);
void sendString_XY (char row, char pos, char *str);
void clearDisplay();


void sendCommand( unsigned char command )
{
	LCD_Port = (LCD_Port & 0b00001111) | (command & 0b11110000); /* sending first four bits */
	LCD_Port &= ~ (1<<RS);										 /* RS=0 to enable command registry */
	LCD_Port |= (1<<EN);									     /* Sending enabling pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0b00001111) | (command << 4);		/* sending last four bits */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void sendCharacter( unsigned char data )
{
	LCD_Port = (LCD_Port & 0b00001111) | (data & 0b11110000);	/* sending first four bits */
	LCD_Port |= (1<<RS);										/* RS=1 to enable data registry */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0b00001111) | (data << 4);			/* sending last four bits */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void initializeLCD (void)			/*Initializing the LCD*/
{
	LCD_DIRECTORY = 0b11111111;	    /*Select LCD port as output */
	_delay_ms(20);			        /* Accommodating power on delay */
	
	sendCommand(0b00000010);				/* Initialize LCD  */
	sendCommand(0b00101000);				/* 2 line, 5*7 matrix in 4-bit mode configurations*/
	sendCommand(0b00001100);				/* Display on cursor off*/
	sendCommand(0b00000110);				/* Increment cursor (shift cursor to right)*/
	sendCommand(0b00000001);				/* Clear display screen*/
	_delay_ms(2);
}


void sendString (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each letter to LCD */
	{
		sendCharacter(str[i]);
	}
}

void sendString_XY (char row, char pos, char *str)	/* Send string to LCD with x,y position */
{
	if (row == 0 && pos<16)
	sendCommand((pos & 0b00001111)|0b10000000);		/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	sendCommand((pos & 0b00001111)|0b11000000);		/* Command of first row and required position<16 */
	sendString(str);								/* Call LCD string function */
}

void clearDisplay()
{
	sendCommand(0b00000001);		/* Command to clear the display */
	_delay_ms(2);
	sendCommand(0b10000000);		/* Set cursor to home */

}


#endif /* LCD_H_ */