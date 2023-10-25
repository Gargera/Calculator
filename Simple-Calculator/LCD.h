#ifndef LCD_H_
#define LCD_H_

#define CLR_SCREEN                     0x01
#define CURSOR_ON_DISPLAY_ON           0x0e
#define CURSOR_OFF_DISPLAY_OFF         0x08
#define CURSOR_OFF_DISPLAY_ON          0x0c
#define CURSOR_BLINKING_DISPLAY_ON     0x0f
#define CURSOR_MOVE_LEFT               0x04
#define RETURN_HOME                    0x02
#define ENTRY_MODE                     0x06
#define FOUR_BITS                      0x28
#define EIGHT_BITS                     0x38

void LCD_init(char portname , char pinnumber , char portname_RW , char pinnumber_RW , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE);
static void LCD_Enable(unsigned char portname , unsigned char pinnumber);
void LCD_vSend_cmd(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE , char cmd);
void LCD_vSend_char(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE , char data);
void LCD_vSend_string(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE , char *data);
void LCD_clearscreen(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE);
void LCD_returnhome(char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE);
void LCD_movecursor(char row , char col , char portname , char pinnumber , char portname_RS , char pinnumber_RS , char portname_EN , char pinnumber_EN , char BITS_MODE);

#endif /* LCD_H_ */