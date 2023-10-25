#include "DIO.h"
#include "LCD.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>

void LCD_init(char portname , char pinnumber , char portname_RW , char pinnumber_RW , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE)
{
	_delay_ms(200);
	
	if(BITS_MODE == 8){
	   DIO_set_port_direction(portname , 0xff);
	}	   
	else{
	   char dir = (((1 << 4) - 1) << pinnumber);
	   DIO_set_port_direction(portname , dir);
	}
	
	DIO_vsetPINDir(portname_EN , pinnumber_EN , 1);
	DIO_vsetPINDir(portname_RW , pinnumber_RW , 1);
	DIO_vsetPINDir(portname_RS , pinnumber_RS , 1);
	DIO_write(portname_RW , pinnumber_RW , 0);
	
	if(BITS_MODE == 8) LCD_vSend_cmd(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , EIGHT_BITS);
	else{
		LCD_returnhome(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE);
		LCD_vSend_cmd(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , FOUR_BITS);
	}
	
	LCD_vSend_cmd(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b01000000);
	
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00000);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00100);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00000);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b11111);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00000);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00100);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00000);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00000);
	
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00000);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b10001);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b01010);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00100);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b01010);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b10001);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00000);
	LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , 0b00000);
	
	LCD_movecursor(1 , 1 , portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE);
	
}

static void LCD_Enable(unsigned char portname , unsigned char pinnumber)
{
	DIO_write(portname,pinnumber,1);
	_delay_ms(2);
	DIO_write(portname,pinnumber,0);
	_delay_ms(2);
}

void LCD_vSend_cmd(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE , char cmd)
{
	if(BITS_MODE == 8){
		DIO_write_port(portname , cmd);
		DIO_write(portname_RS , pinnumber_RS , 0);
		LCD_Enable(portname_EN , pinnumber_EN);
	}
	else{
		DIO_write_nibble(portname , cmd>>4 , pinnumber);
		DIO_write(portname_RS , pinnumber_RS , 0);
		LCD_Enable(portname_EN , pinnumber_EN);
		
		DIO_write_nibble(portname , cmd , pinnumber);
		DIO_write(portname_RS , pinnumber_RS , 0);
		LCD_Enable(portname_EN , pinnumber_EN);
	}
	_delay_ms(1);
}

void LCD_vSend_char(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE , char data)
{
	if(BITS_MODE == 8){
		DIO_write_port(portname , data);
		DIO_write(portname_RS , pinnumber_RS , 1);
		LCD_Enable(portname_EN , pinnumber_EN);
	}
	else{
		DIO_write_nibble(portname , data>>4 , pinnumber);
		DIO_write(portname_RS , pinnumber_RS , 1);
		LCD_Enable(portname_EN , pinnumber_EN);
		
		DIO_write_nibble(portname , data , pinnumber);
		DIO_write(portname_RS , pinnumber_RS , 1);
		LCD_Enable(portname_EN , pinnumber_EN);
	}
	_delay_ms(1);
}

void LCD_vSend_string(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE , char *data)
{
	while((*data) != '\0')
	{
		LCD_vSend_char(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , *data);
		data++;
	}
}

void LCD_clearscreen(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE)
{
	LCD_vSend_cmd(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , CLR_SCREEN);
	_delay_ms(10);
}

void LCD_returnhome(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE)
{
	LCD_vSend_cmd(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , RETURN_HOME);
	_delay_ms(10);
}

void LCD_movecursor(char row , char col , char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE)
{
	char data;
	if(row > 2 || row < 1 || col > 16 || col < 1)
	{
		data = 0x80;
	}
	else if(row == 1)
	{
		data = 0x80 + col - 1;
	}
	else if (row == 2)
	{
		data = 0xc0 + col - 1;
	}
	LCD_vSend_cmd(portname , pinnumber , portname_RS , pinnumber_RS , portname_EN , pinnumber_EN , BITS_MODE , data);
}