#include "DIO.h"
#include "KEYPAD_4X4.h"

void keypad_vInit(unsigned char portname)
{
	DIO_set_port_direction(portname , 0x0f);
	DIO_vconnectpullup(portname,4,1);
	DIO_vconnectpullup(portname,5,1);
	DIO_vconnectpullup(portname,6,1);
	DIO_vconnectpullup(portname,7,1);
}

char keypad_u8check_press(unsigned char portname)
{
   char arr[4][4]={{'7','8','9',0},{'4','5','6',1},{'1','2','3','-'},{'C','0','=','+'}};
   char row , col , x;
   char returnval = NOTPRESSED;
   for(row = 0 ; row < 4 ; row++)
   {
	   DIO_write_port(portname , 0x0f);
	   DIO_write(portname , row , 0);
	
	   for(col = 0 ; col < 4 ; col++)
	   {
		   x = DIO_u8read(portname , col+4);
		   if(x == 0)
		   {
			   returnval = arr[row][col];
			   break;
		   }
	   }
	   if(x == 0)
	   {
		  break;
	   }
    }
    return returnval ;
}