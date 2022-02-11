/*
 * rtc.cpp
 *
 * Created: 6/21/2021 10:05:21 PM
 *  Author: USER
 */ 
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif

#ifndef RTC_h
#define RTC_h
#include <avr/io.h>
#include <util/delay.h>

class RTC{
	public:
	#define RTC_WADDR 0b11010000//*
	#define RTC_RADDR 0b11010001//*
	#define rs PB0//*
	#define en PB1//*
	#define direction DDRD//*?
	#define port PORTD//*?
	RTC(int b);
	void init();
	void i2c_init();
	void i2c_start();
	void i2c_stop();
	void i2c_write(uint8_t data);
	unsigned char i2c_read();
	unsigned char i2c_lastread();
	unsigned char binTobcd(unsigned char data);
	unsigned char bcdTobin(unsigned char data);
	void clock_init();
	void ReadTime(int *sec, int *min, int *hour, int *day, int *wday, int *month, int *year);
	void setTime(int sec, int min, int hour,int day, int mon,int wday, int year);
	void setDate(int day, int mon,int wday, int year);

};

#endif