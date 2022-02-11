/*
 * userInputs.h
 *
 * Created: 6/22/2021 10:43:04 AM
 *  Author: USER
 */ 


#ifndef USERINPUTS_H_
#define USERINPUTS_H_


#include <avr/io.h>
#include <avr/cpufunc.h>
#include "initializePorts.h"

#define SELECT 0
#define DOWN 1
#define UP 2
#define DESELECT 3
#define NOT_SELECTED -1

int buttonInput(){
	int button;
	if ( (1<<BUTTON_SELECT) & PIN_D ) button = SELECT;
	else if ( (1<<BUTTON_DOWN) & PIN_D ) button = DOWN;
	else if ( (1<<BUTTON_UP) & PIN_C ) button = UP;
	else if ( (1<<BUTTON_DESELCT) & PIN_C ) button = DESELECT;
	else button = NOT_SELECTED;
	return button;
}

int keyPadInput(){	int arr1[][3] = {PORTB, PORTB, PORTC};	int arr2[3] = {3,4,5};	int arr3[4] = {3,2,1,0};	int arr4[3] = {6,5,4};	PORTB = 0b00000111;	PORTC = 0b00000010;	int number = 0;	for( int i=0;i<3;i++)	{		DDRB = 0b00000000;		DDRB= (0b00000001 << arr2[i]);				for (int j = 0; j<3;j++)		{			if(!(PINB & (0b00000001<<j)))			{				return (j*3+(i+1));			}					}		if(!(PINC & (0b00000010)))		{			return (number);		}			}		///////////////////////////		return 0xFF;}

#endif /* USERINPUTS_H_ */