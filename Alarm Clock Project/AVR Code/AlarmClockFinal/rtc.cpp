/*
 * rtc.cpp
 *
 * Created: 6/21/2021 10:05:11 PM
 *  Author: USER
 */ 
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "RTC.h"
#include <stdio.h>




RTC::RTC(int b)
{
	int c = b;
	c = c/3;
}

void RTC::i2c_init()
{
    TWBR = 0xFF;
}

void RTC::i2c_start()
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

void RTC::i2c_stop()
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void RTC::i2c_write(unsigned char data)
{
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}
unsigned char RTC::i2c_read()
{
    TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA);
    while ((TWCR & (1 << TWINT)) == 0);
    return TWDR;

}

unsigned char RTC::i2c_lastread()
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
	
}

unsigned char RTC::binTobcd(unsigned char data)
{
   
	
	return( (data/10*16) + (data%10) );
}

unsigned char RTC::bcdTobin(unsigned char data)
{
  
    return( (data/16*10) + (data%16) );
}


void RTC::clock_init()
{
    i2c_start();
    i2c_write(RTC_WADDR);
	i2c_write(0x0E);
	i2c_write(0x20);
	i2c_write(0x08);
    i2c_stop();
	
}

void RTC::setTime(int sec, int min, int hour,int day, int mon,int wday, int year)
{
    i2c_start();
    i2c_write(RTC_WADDR);
    i2c_write(0x00);
    i2c_write(binTobcd(sec));
    i2c_write(binTobcd(min));
    i2c_write(binTobcd(hour));

	i2c_write(binTobcd(wday));
	i2c_write(binTobcd(day));
	i2c_write(binTobcd(mon));
	i2c_write(binTobcd(year));
	i2c_stop();
}

void RTC::ReadTime(int *sec, int *min, int *hour, int *day, int *wday, int *month, int *year)
{
    i2c_start();
    i2c_write(RTC_WADDR);
    i2c_write(0x00);
    i2c_stop();
	
    i2c_start();
    i2c_write(RTC_RADDR);
    *sec = bcdTobin(i2c_read());
    *min = bcdTobin(i2c_read());
    *hour = bcdTobin(i2c_read());

    *wday = bcdTobin(i2c_read());
    *day = bcdTobin(i2c_read());
    *month = bcdTobin(i2c_read());
    *year = bcdTobin(i2c_lastread());
    i2c_stop();

}

void RTC::init()
{
    i2c_init();
	clock_init();
}

