/*
 * initializePorts.h
 *
 * Created: 6/22/2021 10:45:35 AM
 *  Author: USER
 */ 


#ifndef INITIALIZEPORTS_H_
#define INITIALIZEPORTS_H_

//defining busses, ports and pinsS
#define BUS_B DDRB
#define BUS_C DDRC
#define BUS_D DDRD
#define PORT_B PORTB
#define PORT_C PORTC
#define PORT_D PORTD
#define PIN_B PINB
#define PIN_C PINC
#define PIN_D PIND

//defining pins required for lcd
#define RS PORTD0
#define EN PORTD1
#define LCD_DATA0 PORTD4
#define LCD_DATA1 PORTD5
#define LCD_DATA2 PORTD6
#define LCD_DATA3 PORTD7

//defining pins required for keypad
#define KEYPAD_R1 0
#define KEYPAD_R2 1
#define KEYPAD_R3 2
#define KEYPAD_R4 3
#define KEYPAD_C1 4
#define KEYPAD_C2 5
#define KEYPAD_C3 1

//defining pins required for buttons
#define BUTTON_SELECT  2
#define BUTTON_DOWN	   3
#define BUTTON_UP	   2
#define BUTTON_DESELCT 3

//defining pins required for audio-output
#define AUDIO_OUT PORTC0

//defining pins required for rtc
#define RTC_0  PORTC0
#define RTC_1  PORTC1

#include <avr/io.h>

void initializePorts(){
	
	//initialize data direction of port **Check for direction correction
	BUS_B = 0b11110000; 
	BUS_C = 0b0000000;
	BUS_D = 0b11110011;	
	

}

#define SET 0
#define CLEAR 1
#define VIEW 2

#endif /* INITIALIZEPORTS_H_ */