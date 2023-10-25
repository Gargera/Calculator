#ifndef KEYPAD_4X4_H_
#define KEYPAD_4X4_H_

#define NOTPRESSED   0xff

void keypad_vInit(unsigned char portname);
char keypad_u8check_press(unsigned char portname);

#endif /* KEYPAD_4X4_H_ */