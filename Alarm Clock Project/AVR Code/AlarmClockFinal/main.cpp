/*
 * AlarmClockFinal.cpp
 *
 * Created: 6/21/2021 9:56:27 PM
 * Author : USER
 */ 

//defining clock frequency as 16MHz
#define F_CPU 16000000UL

//including library files
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "lcd.h"
#include "userInputs.h"
#include "initializePorts.h"
#include "RTC.h"

int initial = 0;
const float songSpeed = 1.0;
const float songSpeed_G = 1.0;

int var=0;


int maxnumber=2 ;//basic denomination
//int tracknumber;


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int notes[] = {
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,

	NOTE_A4, NOTE_A4,
	//Repeat of first part
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,
	//End of Repeat

	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
	NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4};

// Durations (in ms) of each music note of the song
// Quarter Note is 250 ms when songSpeed = 1.0
int durations[] = {
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,

	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,

	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 125, 250, 125,

	125, 125, 250, 125, 125,
	250, 125, 250, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 375,

	250, 125,
	//Rpeat of First Part
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,

	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,

	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 125, 250, 125,

	125, 125, 250, 125, 125,
	250, 125, 250, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 375,
	//End of Repeat

	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 125, 125, 125, 375,
	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 500,

	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 125, 125, 125, 375,
	250, 125, 375, 250, 125, 375,
125, 125, 125, 125, 125, 500};

int notes_G[]={NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,
	NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_AS3,NOTE_C4,
	NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_C4,NOTE_GS3,NOTE_AS3,
	NOTE_C4,NOTE_F3,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_AS3,
	NOTE_C4,NOTE_D4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,
	NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_AS3,NOTE_C4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,
	NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_C4,NOTE_GS3,NOTE_AS3,NOTE_C4,NOTE_F3,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,
NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_AS3,NOTE_C4,NOTE_D4};

int duration_G[]={500, 500, 250, 250, 500, 500, 250, 250, 1500, 1500, 250, 250, 1000,
	1000, 250, 250, 500, 500, 250, 250, 1500, 1500, 1000, 250, 250, 1000, 1000, 250, 250, 500,
	250, 250, 500, 500, 1000, 1000, 250, 250, 1000, 1000, 250, 250, 500, 500, 250, 250, 500, 500, 500,
	250, 250, 500, 500, 250, 250, 1500, 1500, 250, 250, 1000, 1000, 250, 250, 500, 500, 250, 250, 1500,
	1500, 1000, 250, 250, 1000, 1000, 250, 250, 500, 250, 250, 500, 500, 1000, 1000, 250, 250, 1000, 1000, 250,
250, 500, 500, 250, 250, 500};
int notone[]={9,10,11,13};

int sec, min, hour, day, wday, month, year;
int temp_sec, temp_min, temp_hour, temp_day, temp_wday, temp_month, temp_year;
char* daysOfWeek[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
char* monthsOfYear[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
int prevSecond;
int directory[3];
int tone = 0;
int tempTone = tone;
int key;
int pos=0;
int mode=-1;
char* modeString;
char* tones[3] = {"1.PIRATES ", "2.GOT THEME", "3.DESPACITO"};
bool toDisplay;
int alarmNo = -1;
bool alarms[5] = {false, false, false, false, false};
int alarmTime[5][3] = {0};
bool reset = false;
//bool edit = false;

bool isAlarmActive = false;
char tempString1[17];
char tempString2[17];
void updateTime(int* tempSec, int* tempMin, int* tempHour, int* tempDay, int* tempWday, int* tempMonth, int* tempYear, int *pos, int key);
char temp[4];
RTC rtc(1);

void play_tone(uint16_t delay, uint8_t duration);
void pla();
void sto();
void del(int ms);
int GameOfThrones();
void play_();

/*ISR (INT0_vect)          //External interrupt_zero ISR
{
	pla();
	
	
}
ISR (INT1_vect)        //External interrupt_one ISR
{
	sto();
}*/

int main(){
	initializeLCD();
	rtc.init();
	rtc.setTime(0,0,0,1,1,4,21);
	toDisplay = true;

	// internal RC oscillator calibration for 8MHz.
	//OSCCAL = 176;

	// enable the piezo as output
	DDRC |= (1<<PC0);
	
	/*// enable internal pullup on PA7 (the button)
	PORTD |= (1<<PD7)|(1<<PD6)|(1<<PD2)|(1<<PD3);
	
	EICRA |= (1 << ISC01)|(1 << ISC11);    // set INT0 to trigger on ANY logic change
	EIMSK |= (1 << INT0)|(1 << INT1);
	sei();*/
	
	int button;
	while(1){
		

		_delay_ms(200);
		
		button = buttonInput();
		rtc.ReadTime(&sec, &min, &hour, &day, &wday, &month, &year);
		key = keyPadInput();


		
		for (int i=0; i<5; i++){	
			if((alarmTime[i][0] == hour) && (alarmTime[i][1] == min)) {
				//PORTC = 0b00000001;
				isAlarmActive = true;
			}
			
		}	
		if (isAlarmActive){
			
			PORTC |= (1<<PORTC0);
			_delay_ms(1000);
			pla();
			play_();
			
		}
		
		switch(directory[0]){
			
			case 0://timeDisplay
			
				if (toDisplay){
					clearDisplay();
					prevSecond = sec;
					sprintf(tempString1,"%02d-%s/%s/%02d", day, daysOfWeek[wday], monthsOfYear[month], year);
					sprintf(tempString2,"%02d:%02d:%02d", hour, min, sec);
					sendString_XY(0,2,tempString1);
					sendString_XY(1,4,tempString2);
					toDisplay = false;
				}
				
				else if (sec!=prevSecond){
					prevSecond = sec;
					sprintf(tempString1,"%02d-%s/%s/%02d", day, daysOfWeek[wday], monthsOfYear[month], year);
					sprintf(tempString2,"%02d:%02d:%02d", hour, min, sec);
					sendString_XY(0,2,tempString1);
					sendString_XY(1,4,tempString2);
				}
				
				if (button == DOWN){
					directory[0] = 1;//edit this
					toDisplay = true;
				}
				
				break;
			
			case 1://setTime
				switch(directory[1]){
					case 0:
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,0,"    SETTINGS");
							sendString_XY(1,0,"  1.EDIT TIME");
							toDisplay = false;
						}
						
						if (button == UP) {
							directory[0] = 0;
							toDisplay = true;
						}
						else if (button == DOWN) {
							directory[0]=2;
							toDisplay = true;
						}
						else if (button == SELECT) {
							directory[1]=1;
							toDisplay = true;
							clearDisplay();
						}
						break;
												
					case 1:
						if (toDisplay){
							clearDisplay();
							temp_sec  = sec;
							temp_min  = min;
							temp_hour = hour;
							temp_day  = day;
							temp_wday = wday;
							temp_month = month;
							temp_year = year;
							
							sprintf(tempString1, "%02d-%s/%s/%02d",temp_day, daysOfWeek[temp_wday], monthsOfYear[temp_month],year);
							sprintf(tempString2,"%02d:%02d:%02d", temp_hour, temp_min, temp_sec);
							sendString_XY(0,2,tempString1);
							sendString_XY(1,4, tempString2);
							toDisplay = false;
							
						}
						
						if (button == DESELECT){
							toDisplay = true;
							directory[1] = 0;
						}
						
						else if (key!=255){
							updateTime(&temp_sec, &temp_min, &temp_hour, &temp_day, &temp_wday, &temp_month, &temp_year, &pos, key);
							sprintf(tempString1, "%02d-%s/%s/%02d",temp_day, daysOfWeek[temp_wday], monthsOfYear[temp_month],temp_year);
							sprintf(tempString2,"%02d:%02d:%02d", temp_hour, temp_min, temp_sec);
							sendString_XY(0,2,tempString1);
							sendString_XY(1,4, tempString2);
							if (pos==13){
								pos = 0;
								rtc.setTime(temp_sec, temp_min, temp_hour, temp_day, temp_month, temp_wday, temp_year);
								directory[1]=0;
								toDisplay = true;
							}
						}
						
						
						break;
				}
				
				break;

				
			case 2://setAlarm
				switch(directory[1]){
					case 0:
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,0,"    SETTINGS");
							sendString_XY(1,0," 2.EDIT ALARMS");
							toDisplay = false;
						}
						
						if (button == UP) {
							directory[0] = 1;
							toDisplay = true;
						}
						else if (button == DOWN) {
							directory[0]=3;
							toDisplay = true;
						}
						else if (button == SELECT) {
							directory[1]=1;
							toDisplay = true;
							clearDisplay();
						}
						break;					
						
					
					case 1:
						if (toDisplay){
							sendString_XY(0,0,"ENTER ALARM:");
							sendString_XY(0,13,"_");
							toDisplay = false;
						}
						
						if (button == UP) alarmNo = (alarmNo+1)%5;
			
						else if (button == DOWN){
							alarmNo = alarmNo-1;
							if (alarmNo<0) alarmNo =0;
							alarmNo = alarmNo%5;
						}
						
						else if (button == SELECT){
							if (alarmNo!=-1){
								toDisplay = true;
								directory[1]=2;
							}
						}
						
						else if (button == DESELECT){
							alarmNo = -1;
							directory[1]=0;
							toDisplay = true;
						}
							
						sprintf(tempString1, "ENTER ALARM: %d ", alarmNo+1);
						sendString_XY(0,0,tempString1);
						
						break;
						
					case 2:
					
						if (toDisplay){
							sendString_XY(1,0,"ENTER MODE:");
							sendString_XY(1,13,"_");
							toDisplay = false;
						}
						
						if (button == UP) mode = (mode+1)%3;
						
						else if (button == DOWN){
							mode = mode-1;
							if (mode<0) mode =4;
							mode = mode%3;
						}
						
						else if (button == SELECT){
							if (mode!=-1){
								toDisplay = true;
								directory[1]=3;
								if (mode==SET) pos = 7;
							}
						}
						
						else if (button == DESELECT){
							mode = -1;
							alarmNo = -1;							
							directory[1]=0;
							toDisplay = true;

							
						}
						if (mode==SET) modeString = "SET";
						else if (mode==CLEAR) modeString = "CLR";
						else if (mode==VIEW) modeString ="VIEW";
						
						sprintf(tempString1, "ENTER MODE: %s ", modeString);
						sendString_XY(1,0,tempString1);						
						
						break;
						
					case 3:
						if (mode == CLEAR){
							alarmTime[alarmNo][0] = 0;
							alarmTime[alarmNo][1] = 0;
							alarmTime[alarmNo][2] = 0;
							alarms[alarmNo] = false;
							toDisplay = true;
							directory[1]=0;
						}
						else if (mode == SET){
							if (toDisplay) {
								clearDisplay();
								toDisplay = false;
							}
							if (key!=255){
								updateTime(&alarmTime[alarmNo][2], &alarmTime[alarmNo][1], &alarmTime[alarmNo][0], &temp_day, &temp_wday, &temp_month, &temp_year, &pos, key);
								if (pos==13){
									alarms[alarmNo] = true;
									pos = 0;
									directory[1]=0;
									toDisplay = true;
								}
							}
					
								sprintf(tempString1,"%02d:%02d:%02d", alarmTime[alarmNo][0], alarmTime[alarmNo][1], alarmTime[alarmNo][2]);
								sendString_XY(0,0,tempString1);		
								_delay_ms(200);
								sendString_XY(0,((pos-7)/2)*2+(pos-6)/2,"_");					
						}
						
						else if (mode==VIEW){
							if (toDisplay){
								clearDisplay();
								toDisplay = false;
							}
							sprintf(tempString1,"%02d:%02d:%02d", alarmTime[alarmNo][0], alarmTime[alarmNo][1], alarmTime[alarmNo][2]);
							sendString_XY(0,0,tempString1);		
							
							if (alarms[alarmNo]) sprintf(tempString2,"ACTIVE");
							else sprintf(tempString2,"INACTIVE");
							sendString_XY(1,0,tempString2);
							
							if (button==DESELECT) {
								toDisplay = true;
								directory[1]=0;
							}
						}
						break;
				}
				
				break;
				
			case 3://setTone
				switch(directory[1]){
					case 0:
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,0,"    SETTINGS");
							sendString_XY(1,0,"  3.EDIT TONE");
							toDisplay = false;
						}
                        
						if (button == UP) {
							directory[0] = 2;
							toDisplay = true;
						}
						else if (button == DOWN) {
							directory[0] = 4;
							toDisplay = true;
						}
						else if (button == SELECT) {
							directory[1]=1;
							toDisplay = true;
						}
						break;
						
					
					case 1:
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,0,tones[tempTone]);
							toDisplay = false;
						}
						
						if (button == UP) {
							if (tempTone!=0) tempTone = (tempTone-1)%3;
							else tempTone = 2;
							toDisplay = true;
						}
						else if (button == DOWN) {
							tempTone = (tempTone+1)%3;
							toDisplay = true;
						}
						else if (button == SELECT) {
							tone = tempTone;
							directory[1] = 0;
							toDisplay = true;
						}
			
						else if (button == DESELECT) {
							tempTone = tone;
							directory[1] = 0;
							toDisplay = true;
						}
						break;
				}
				break;
			
			case 4://Reset
			
				switch(directory[1]){
					case 0:
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,0,"    SETTINGS");
							sendString_XY(1,0,"    4.RESET");
							toDisplay = false;
						}
					
						if (button == UP) {
							directory[0] = 3;
							toDisplay = true;
						}
						else if (button == SELECT) {
							directory[1]=1;
							toDisplay = true;
						}
						break;
					
					
					case 1:
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,0,"CONFIRM RESET");
							toDisplay = false;
						}
					
						if (button == UP || button == DOWN) {
							reset = !reset;
							if (reset) sendString_XY(1,0,"Y");
							else sendString_XY(1,0,"n");
						}

						else if (button == SELECT) {
							if (reset){
							directory[1] = 0;
							toDisplay = true;
							}
						}
					
						else if (button == DESELECT) {
							reset = false;
							directory[1] = 0;
							toDisplay = true;
						}
						break;
					}
			default: 
				break;
			
			
			
			
			
		}//directory_0_Switch
		
	}
}


void updateTime(int* tempSec, int* tempMin, int* tempHour, int* tempDay, int* tempWday, int* tempMonth, int* tempYear, int *pos, int key){
	switch(*pos){
		
		case 0:
			*tempYear = key*10+*tempYear%10;
			_delay_ms(500);
			break;
			
		case 1:
			*tempYear = 10*(*tempYear/10)+key;
			_delay_ms(500);
			break;
			
		case 2:
			if (key<2) *tempMonth = key*10+*tempMonth%10;
			_delay_ms(500);
			break;
			
		case 3:
			*tempMonth = 10*(*tempMonth/10)+key-1;
			if (*tempMonth<0) *tempMonth=0;
			else if (*tempMonth>=12) *tempMonth = 11;
			_delay_ms(500);
			break;
		//Day calculation is need very hard to code this	
		case 4:
			if (*tempMonth!=1 && key<=3) *tempDay = key*10+*tempDay%10;
			else if (*tempDay==1 && key<=2) *tempDay = key*10+*tempDay%10;
			_delay_ms(500);
			break;
			
			
		case 5:
			*tempDay = 10*(*tempDay/10)+key;
			if ((*tempMonth==0 || *tempMonth==2 || *tempMonth==4 || *tempMonth==6 || *tempMonth==7 || *tempMonth==9 || *tempMonth==11)&& *tempDay>31) *tempDay =31;
			else if ((*tempMonth==3 || *tempMonth==5 || *tempMonth==8 || *tempMonth==10) && *tempDay>30) *tempDay =30;
			else if (*tempMonth==1 && *tempYear==0 && *tempDay>28) *tempDay = 28;
			else if (*tempMonth==1 && *tempYear%4==0 && *tempDay>29) *tempDay =29;
			_delay_ms(500);
			break;
		
		case 6:
			if (key<=7 && key>=1) *tempWday = key-1;
			_delay_ms(500);
			break;
			
		case 7:
			if (key<=2) *tempHour = key*10+*tempHour%10;
			_delay_ms(500);
			break;
			
		case 8:
			if ((*tempHour>=20 && key<=3) ||(*tempHour<20)) *tempHour = 10*(*tempHour/10)+key;
			_delay_ms(500);
			break;
			
		case 9:
			if (key<=5) *tempMin = 10*key + *tempMin%10;
			_delay_ms(500);
			break;
		
		case  10:
			*tempMin = 10*(*tempMin/10)+key;
			_delay_ms(500);
			break;
		
		case 11:
			if (key<=5) *tempSec = 10*key + *tempSec%10;
			_delay_ms(500);
			break;
		
		case 12:
			*tempSec = 10*(*tempSec/10)+key;
			_delay_ms(500);
			break;
		
	}
		
		*pos = *pos+1;
		
	
}

void play_tone(uint16_t delay, uint8_t duration) {
	// delay is half-period in microseconds
	// duration is in 10ms increments
	
	// example: 440Hz --> delay=1136
	
	
	// duration = 2*delay * cycles (all in same units)
	// cycles = 10000 * duration / delay / 2
	// cycles = 100 * duration / (delay/50)
	uint16_t tmp = 100 * duration;
	uint16_t delaysm = delay / 50;
	uint16_t cycles = tmp / delaysm;
	
	while(cycles > 0) {
		if (delay==NOTE_DS8){
			PORTC |= (1<<PC0);
			_delay_us(31);
			PORTC &= ~(1<<PC0);
		_delay_us(31);}


		if (delay==NOTE_D8){
			PORTC |= (1<<PC0);
			_delay_us(33);
			PORTC &= ~(1<<PC0);
		_delay_us(33);}


		if (delay==NOTE_CS8){
			PORTC |= (1<<PC0);
			_delay_us(35);
			PORTC &= ~(1<<PC0);
		_delay_us(35);}


		if (delay==NOTE_C8){
			PORTC |= (1<<PC0);
			_delay_us(37);
			PORTC &= ~(1<<PC0);
		_delay_us(37);}


		if (delay==NOTE_B7){
			PORTC |= (1<<PC0);
			_delay_us(39);
			PORTC &= ~(1<<PC0);
		_delay_us(39);}


		if (delay==NOTE_AS7){
			PORTC |= (1<<PC0);
			_delay_us(41);
			PORTC &= ~(1<<PC0);
		_delay_us(41);}


		if (delay==NOTE_A7){
			PORTC |= (1<<PC0);
			_delay_us(44);
			PORTC &= ~(1<<PC0);
		_delay_us(44);}


		if (delay==NOTE_GS7){
			PORTC |= (1<<PC0);
			_delay_us(46);
			PORTC &= ~(1<<PC0);
		_delay_us(46);}


		if (delay==NOTE_G7){
			PORTC |= (1<<PC0);
			_delay_us(49);
			PORTC &= ~(1<<PC0);
		_delay_us(49);}


		if (delay==NOTE_FS7){
			PORTC |= (1<<PC0);
			_delay_us(52);
			PORTC &= ~(1<<PC0);
		_delay_us(52);}


		if (delay==NOTE_F7){
			PORTC |= (1<<PC0);
			_delay_us(55);
			PORTC &= ~(1<<PC0);
		_delay_us(55);}


		if (delay==NOTE_E7){
			PORTC |= (1<<PC0);
			_delay_us(58);
			PORTC &= ~(1<<PC0);
		_delay_us(58);}


		if (delay==NOTE_DS7){
			PORTC |= (1<<PC0);
			_delay_us(62);
			PORTC &= ~(1<<PC0);
		_delay_us(62);}


		if (delay==NOTE_D7){
			PORTC |= (1<<PC0);
			_delay_us(65);
			PORTC &= ~(1<<PC0);
		_delay_us(65);}


		if (delay==NOTE_CS7){
			PORTC |= (1<<PC0);
			_delay_us(69);
			PORTC &= ~(1<<PC0);
		_delay_us(69);}


		if (delay==NOTE_C7){
			PORTC |= (1<<PC0);
			_delay_us(73);
			PORTC &= ~(1<<PC0);
		_delay_us(73);}


		if (delay==NOTE_B6){
			PORTC |= (1<<PC0);
			_delay_us(78);
			PORTC &= ~(1<<PC0);
		_delay_us(78);}


		if (delay==NOTE_AS6){
			PORTC |= (1<<PC0);
			_delay_us(82);
			PORTC &= ~(1<<PC0);
		_delay_us(82);}


		if (delay==NOTE_A6){
			PORTC |= (1<<PC0);
			_delay_us(87);
			PORTC &= ~(1<<PC0);
		_delay_us(87);}


		if (delay==NOTE_GS6){
			PORTC |= (1<<PC0);
			_delay_us(93);
			PORTC &= ~(1<<PC0);
		_delay_us(93);}


		if (delay==NOTE_G6){
			PORTC |= (1<<PC0);
			_delay_us(98);
			PORTC &= ~(1<<PC0);
		_delay_us(98);}


		if (delay==NOTE_FS6){
			PORTC |= (1<<PC0);
			_delay_us(104);
			PORTC &= ~(1<<PC0);
		_delay_us(104);}


		if (delay==NOTE_F6){
			PORTC |= (1<<PC0);
			_delay_us(110);
			PORTC &= ~(1<<PC0);
		_delay_us(110);}


		if (delay==NOTE_E6){
			PORTC |= (1<<PC0);
			_delay_us(117);
			PORTC &= ~(1<<PC0);
		_delay_us(117);}


		if (delay==NOTE_DS6){
			PORTC |= (1<<PC0);
			_delay_us(123);
			PORTC &= ~(1<<PC0);
		_delay_us(123);}


		if (delay==NOTE_D6){
			PORTC |= (1<<PC0);
			_delay_us(131);
			PORTC &= ~(1<<PC0);
		_delay_us(131);}


		if (delay==NOTE_CS6){
			PORTC |= (1<<PC0);
			_delay_us(139);
			PORTC &= ~(1<<PC0);
		_delay_us(139);}


		if (delay==NOTE_C6){
			PORTC |= (1<<PC0);
			_delay_us(147);
			PORTC &= ~(1<<PC0);
		_delay_us(147);}


		if (delay==NOTE_B5){
			PORTC |= (1<<PC0);
			_delay_us(156);
			PORTC &= ~(1<<PC0);
		_delay_us(156);}


		if (delay==NOTE_AS5){
			PORTC |= (1<<PC0);
			_delay_us(165);
			PORTC &= ~(1<<PC0);
		_delay_us(165);}


		if (delay==NOTE_A5){
			PORTC |= (1<<PC0);
			_delay_us(175);
			PORTC &= ~(1<<PC0);
		_delay_us(175);}


		if (delay==NOTE_GS5){
			PORTC |= (1<<PC0);
			_delay_us(185);
			PORTC &= ~(1<<PC0);
		_delay_us(185);}


		if (delay==NOTE_G5){
			PORTC |= (1<<PC0);
			_delay_us(196);
			PORTC &= ~(1<<PC0);
		_delay_us(196);}


		if (delay==NOTE_FS5){
			PORTC |= (1<<PC0);
			_delay_us(208);
			PORTC &= ~(1<<PC0);
		_delay_us(208);}


		if (delay==NOTE_F5){
			PORTC |= (1<<PC0);
			_delay_us(220);
			PORTC &= ~(1<<PC0);
		_delay_us(220);}


		if (delay==NOTE_E5){
			PORTC |= (1<<PC0);
			_delay_us(233);
			PORTC &= ~(1<<PC0);
		_delay_us(233);}


		if (delay==NOTE_DS5){
			PORTC |= (1<<PC0);
			_delay_us(247);
			PORTC &= ~(1<<PC0);
		_delay_us(247);}


		if (delay==NOTE_D5){
			PORTC |= (1<<PC0);
			_delay_us(262);
			PORTC &= ~(1<<PC0);
		_delay_us(262);}


		if (delay==NOTE_CS5){
			PORTC |= (1<<PC0);
			_delay_us(277);
			PORTC &= ~(1<<PC0);
		_delay_us(277);}


		if (delay==NOTE_C5){
			PORTC |= (1<<PC0);
			_delay_us(294);
			PORTC &= ~(1<<PC0);
		_delay_us(294);}


		if (delay==NOTE_B4){
			PORTC |= (1<<PC0);
			_delay_us(311);
			PORTC &= ~(1<<PC0);
		_delay_us(311);}


		if (delay==NOTE_AS4){
			PORTC |= (1<<PC0);
			_delay_us(330);
			PORTC &= ~(1<<PC0);
		_delay_us(330);}


		if (delay==NOTE_A4){
			PORTC |= (1<<PC0);
			_delay_us(349);
			PORTC &= ~(1<<PC0);
		_delay_us(349);}


		if (delay==NOTE_GS4){
			PORTC |= (1<<PC0);
			_delay_us(370);
			PORTC &= ~(1<<PC0);
		_delay_us(370);}


		if (delay==NOTE_G4){
			PORTC |= (1<<PC0);
			_delay_us(392);
			PORTC &= ~(1<<PC0);
		_delay_us(392);}


		if (delay==NOTE_FS4){
			PORTC |= (1<<PC0);
			_delay_us(415);
			PORTC &= ~(1<<PC0);
		_delay_us(415);}


		if (delay==NOTE_F4){
			PORTC |= (1<<PC0);
			_delay_us(440);
			PORTC &= ~(1<<PC0);
		_delay_us(440);}


		if (delay==NOTE_E4){
			PORTC |= (1<<PC0);
			_delay_us(466);
			PORTC &= ~(1<<PC0);
		_delay_us(466);}


		if (delay==NOTE_DS4){
			PORTC |= (1<<PC0);
			_delay_us(494);
			PORTC &= ~(1<<PC0);
		_delay_us(494);}


		if (delay==NOTE_D4){
			PORTC |= (1<<PC0);
			_delay_us(523);
			PORTC &= ~(1<<PC0);
		_delay_us(523);}


		if (delay==NOTE_CS4){
			PORTC |= (1<<PC0);
			_delay_us(554);
			PORTC &= ~(1<<PC0);
		_delay_us(554);}


		if (delay==NOTE_C4){
			PORTC |= (1<<PC0);
			_delay_us(587);
			PORTC &= ~(1<<PC0);
		_delay_us(587);}


		if (delay==NOTE_B3){
			PORTC |= (1<<PC0);
			_delay_us(622);
			PORTC &= ~(1<<PC0);
		_delay_us(622);}


		if (delay==NOTE_AS3){
			PORTC |= (1<<PC0);
			_delay_us(659);
			PORTC &= ~(1<<PC0);
		_delay_us(659);}


		if (delay==NOTE_A3){
			PORTC |= (1<<PC0);
			_delay_us(698);
			PORTC &= ~(1<<PC0);
		_delay_us(698);}


		if (delay==NOTE_GS3){
			PORTC |= (1<<PC0);
			_delay_us(740);
			PORTC &= ~(1<<PC0);
		_delay_us(740);}


		if (delay==NOTE_G3){
			PORTC |= (1<<PC0);
			_delay_us(784);
			PORTC &= ~(1<<PC0);
		_delay_us(784);}


		if (delay==NOTE_FS3){
			PORTC |= (1<<PC0);
			_delay_us(831);
			PORTC &= ~(1<<PC0);
		_delay_us(831);}


		if (delay==NOTE_F3){
			PORTC |= (1<<PC0);
			_delay_us(880);
			PORTC &= ~(1<<PC0);
		_delay_us(880);}


		if (delay==NOTE_E3){
			PORTC |= (1<<PC0);
			_delay_us(932);
			PORTC &= ~(1<<PC0);
		_delay_us(932);}


		if (delay==NOTE_DS3){
			PORTC |= (1<<PC0);
			_delay_us(988);
			PORTC &= ~(1<<PC0);
		_delay_us(988);}


		if (delay==NOTE_D3){
			PORTC |= (1<<PC0);
			_delay_us(1047);
			PORTC &= ~(1<<PC0);
		_delay_us(1047);}


		if (delay==NOTE_CS3){
			PORTC |= (1<<PC0);
			_delay_us(1109);
			PORTC &= ~(1<<PC0);
		_delay_us(1109);}


		if (delay==NOTE_C3){
			PORTC |= (1<<PC0);
			_delay_us(1175);
			PORTC &= ~(1<<PC0);
		_delay_us(1175);}


		if (delay==NOTE_B2){
			PORTC |= (1<<PC0);
			_delay_us(1245);
			PORTC &= ~(1<<PC0);
		_delay_us(1245);}


		if (delay==NOTE_AS2){
			PORTC |= (1<<PC0);
			_delay_us(1319);
			PORTC &= ~(1<<PC0);
		_delay_us(1319);}


		if (delay==NOTE_A2){
			PORTC |= (1<<PC0);
			_delay_us(1397);
			PORTC &= ~(1<<PC0);
		_delay_us(1397);}


		if (delay==NOTE_GS2){
			PORTC |= (1<<PC0);
			_delay_us(1480);
			PORTC &= ~(1<<PC0);
		_delay_us(1480);}


		if (delay==NOTE_G2){
			PORTC |= (1<<PC0);
			_delay_us(1568);
			PORTC &= ~(1<<PC0);
		_delay_us(1568);}


		if (delay==NOTE_FS2){
			PORTC |= (1<<PC0);
			_delay_us(1661);
			PORTC &= ~(1<<PC0);
		_delay_us(1661);}


		if (delay==NOTE_F2){
			PORTC |= (1<<PC0);
			_delay_us(1760);
			PORTC &= ~(1<<PC0);
		_delay_us(1760);}


		if (delay==NOTE_E2){
			PORTC |= (1<<PC0);
			_delay_us(1865);
			PORTC &= ~(1<<PC0);
		_delay_us(1865);}


		if (delay==NOTE_DS2){
			PORTC |= (1<<PC0);
			_delay_us(1976);
			PORTC &= ~(1<<PC0);
		_delay_us(1976);}


		if (delay==NOTE_D2){
			PORTC |= (1<<PC0);
			_delay_us(2093);
			PORTC &= ~(1<<PC0);
		_delay_us(2093);}


		if (delay==NOTE_CS2){
			PORTC |= (1<<PC0);
			_delay_us(2217);
			PORTC &= ~(1<<PC0);
		_delay_us(2217);}


		if (delay==NOTE_C2){
			PORTC |= (1<<PC0);
			_delay_us(2349);
			PORTC &= ~(1<<PC0);
		_delay_us(2349);}


		if (delay==NOTE_B1){
			PORTC |= (1<<PC0);
			_delay_us(2489);
			PORTC &= ~(1<<PC0);
		_delay_us(2489);}


		if (delay==NOTE_AS1){
			PORTC |= (1<<PC0);
			_delay_us(2637);
			PORTC &= ~(1<<PC0);
		_delay_us(2637);}


		if (delay==NOTE_A1){
			PORTC |= (1<<PC0);
			_delay_us(2794);
			PORTC &= ~(1<<PC0);
		_delay_us(2794);}


		if (delay==NOTE_GS1){
			PORTC |= (1<<PC0);
			_delay_us(2960);
			PORTC &= ~(1<<PC0);
		_delay_us(2960);}


		if (delay==NOTE_G1){
			PORTC |= (1<<PC0);
			_delay_us(3136);
			PORTC &= ~(1<<PC0);
		_delay_us(3136);}


		if (delay==NOTE_FS1){
			PORTC |= (1<<PC0);
			_delay_us(3322);
			PORTC &= ~(1<<PC0);
		_delay_us(3322);}


		if (delay==NOTE_F1){
			PORTC |= (1<<PC0);
			_delay_us(3520);
			PORTC &= ~(1<<PC0);
		_delay_us(3520);}


		if (delay==NOTE_E1){
			PORTC |= (1<<PC0);
			_delay_us(3729);
			PORTC &= ~(1<<PC0);
		_delay_us(3729);}


		if (delay==NOTE_DS1){
			PORTC |= (1<<PC0);
			_delay_us(3951);
			PORTC &= ~(1<<PC0);
		_delay_us(3951);}


		if (delay==NOTE_D1){
			PORTC |= (1<<PC0);
			_delay_us(4186);
			PORTC &= ~(1<<PC0);
		_delay_us(4186);}


		if (delay==NOTE_CS1){
			PORTC |= (1<<PC0);
			_delay_us(4435);
			PORTC &= ~(1<<PC0);
		_delay_us(4435);}


		if (delay==NOTE_C1){
			PORTC |= (1<<PC0);
			_delay_us(4699);
			PORTC &= ~(1<<PC0);
		_delay_us(4699);}


		if (delay==NOTE_B0){
			PORTC |= (1<<PC0);
			_delay_us(4978);
			PORTC &= ~(1<<PC0);
		_delay_us(4978);}

		cycles--;
		
	}
}

void pla(){

var=1;}

void sto(){
	var=0;
}

void del(int ms){
	while(ms--){_delay_ms(1);}}

	int Pirates()
	{
		const int totalNotes = sizeof(notes) / sizeof(int);
		// Loop through each note
		for (int i = 0; i < totalNotes; i++)
		{if (var==0){
		return 0;}
		
		
		const int currentNote = notes[i];
		int wait = durations[i] / songSpeed;
		// Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
		if (currentNote !=0){
		play_tone( notes[i], wait/50); }
		
		// delay is used to wait for tone to finish playing before moving to next loop
		else{del(wait/10-0.5);}
		del(wait/10-5.5);
	}
}
int GameOfThrones(){
	const int totalNotes = sizeof(notes) / sizeof(int);
	// Loop through each note
	for (int i = 0; i < totalNotes; i++)
	{if (var==0){
	return 0;}
	
	
	const int currentNote = notes[i];
	int wait = durations[i] / songSpeed;
	// Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
	if (currentNote !=0){
	play_tone( notes[i], wait/50); }
	
	// delay is used to wait for tone to finish playing before moving to next loop
	
	else{del(wait/10-0.5);}
	del(wait/10-5.5);
}
}
void play_(){
	if(tone ==0){Pirates();
	}
	else{if(tone==1){GameOfThrones();
	}}
}