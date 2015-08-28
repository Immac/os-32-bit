#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <../kernel/low_level.h>
#include <../kernel/system.h>
#include <screen.h>
#include <../util/queue.h>


void keyboard_handler(struct regs *r);
void init_keyboard(void);
unsigned char Keyboard_ReadKey(void);


#endif //_KEYBOARD_H_
