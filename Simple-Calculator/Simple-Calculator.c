#include "LCD.h"
#include "KEYPAD_4x4.h"

#define  MAX_UNUSED     1000

int main(void)
{
	LCD_init('A' , 0 , 'A' , 5 , 'A' , 6 , 'A' , 4 , 4);
	keypad_vInit('C');
	
	char on = 0 , counter = 0 , calc[16] , counter_to_off = 0 , ERROR = 0 , EQUAL_PRESSED = 0;
	
    while(1)
    {
        char read_char = keypad_u8check_press('C');
		
		if(read_char == NOTPRESSED || (ERROR == 1 && read_char != 'C')){
		    if(on == 1){
				counter_to_off++;
				
				if(counter_to_off == MAX_UNUSED){
					LCD_clearscreen('A' , 0 , 'A' , 6 , 'A' , 4 , 4);
					LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , CURSOR_OFF_DISPLAY_OFF);
					counter = 0;
					counter_to_off = 0;
					ERROR = 0;
					EQUAL_PRESSED = 0;
					on = 0;
				}
			}
		}
		else if(read_char == 'C'){
			LCD_clearscreen('A' , 0 , 'A' , 6 , 'A' , 4 , 4);
			LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , CURSOR_BLINKING_DISPLAY_ON);
			LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , ENTRY_MODE);
			counter = 0;
			counter_to_off = 0;
			ERROR = 0;
			EQUAL_PRESSED = 0;
			on = 1;
		}
		else{
			if(on == 1 && ERROR == 0){
			   if(EQUAL_PRESSED == 1){
				   LCD_clearscreen('A' , 0 , 'A' , 6 , 'A' , 4 , 4);
				   LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , CURSOR_BLINKING_DISPLAY_ON);
				   LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , ENTRY_MODE);
				   counter = 0;
				   ERROR = 0;
				   EQUAL_PRESSED = 0;
			   }
			   
			   counter_to_off = 0;
			   
		       if(read_char == '='){
			       char SYNTAX_ERROR = 0;
			       for(char i = 1 ; i < counter ; i++){
				         if(!isdigit(calc[i]) && !isdigit(calc[i-1])){
					               SYNTAX_ERROR = 1;
					               break;
				         }
			       }
				
				   if(counter != 0 && (!isdigit(calc[0]) || !isdigit(calc[counter - 1]))){
					     SYNTAX_ERROR = 1;
				   }
				   
				   if(SYNTAX_ERROR == 1){
					     LCD_clearscreen('A' , 0 , 'A' , 6 , 'A' , 4 , 4);
					     LCD_movecursor(1 , 3 , 'A' , 0 , 'A' , 6 , 'A' , 4 , 4);
					     LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , CURSOR_OFF_DISPLAY_ON);
					     LCD_vSend_string('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , "SYNTAX ERROR");
					     counter = 0;
					     ERROR = 1;
				   }
				   else{
				         long long ans = 0;
				         char i;
				         for(i = 0 ; i < counter ; i++){
				             if(isdigit(calc[i])){
						          ans *= 10;
						          ans += calc[i] - '0';
					         }
					         else{
					              break;
					         }						   
				         }
				   
				         for( ; i < counter ; i++){
				             if(!isdigit(calc[i])){
						          long long num = 0;
						          for(char j = i+1 ; j < counter ; j++){
						               if(isdigit(calc[j])){
								             num *= 10;
								             num += calc[j] - '0';
							           }
							           else{
								             break;
							           }
						           }
						   
						           if(calc[i] == '+'){
						               ans += num;
						           }			
						           else if(calc[i] == '-'){
		                               ans -= num;
						           }
						           else if(calc[i] == 1){
							           ans *= num;
						           }
						           else if(calc[i] == 0){
							           if(num == 0){
							                 LCD_clearscreen('A' , 0 , 'A' , 6 , 'A' , 4 , 4);
							                 LCD_movecursor(1 , 4 , 'A' , 0 , 'A' , 6 , 'A' , 4 , 4);
							                 LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , CURSOR_OFF_DISPLAY_ON);
							                 LCD_vSend_string('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , "MATH ERROR");
							                 counter = 0;
							                 ERROR = 1;
											 break;
							           }
							           else{
								             ans /= num;
							           }
						           }
							 }
						 }																					   
						   
						 if(ERROR == 0){
						     char neg = 0;
							 if(ans < 0){
								 neg = 1;
								 ans *= -1;
							 }										   
							   
							 LCD_movecursor(2 , 16 , 'A' , 0 , 'A' , 6 , 'A' , 4 , 4);
						     LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , CURSOR_MOVE_LEFT);
							 if(ans == 0){
								  LCD_vSend_char('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , '0');
							 }
							 else{
							      while(ans > 0){
									   LCD_vSend_char('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , ans%10 + '0');
								       ans /= 10;
								  }
							 }   
							   
							  if(neg == 1){
							       LCD_vSend_char('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , '-');
							  }
							   
							  LCD_vSend_cmd('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , CURSOR_OFF_DISPLAY_ON);
							  EQUAL_PRESSED = 1;				   								   
						 }
				   }								   							   				   							   
			   }
			   else{
				   if(counter < 16){
					    calc[counter] = read_char;
					    counter++;
					    LCD_vSend_char('A' , 0 , 'A' , 6 , 'A' , 4 , 4 , read_char);
				   }
			   }
		   }
	    }							
        while(keypad_u8check_press('C') == read_char);
	}
}