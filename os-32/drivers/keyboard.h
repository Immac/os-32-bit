#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <../kernel/low_level.h>
#include <../kernel/system.h>
#include <screen.h>

void keyboard_handler(struct regs *r);
void init_keyboard(void);
struct keyboard_status
{
    unsigned char buffer[255];
    unsigned int start;
    unsigned int current;
    unsigned int lock_flags;
    unsigned int modifier_keys_flags;
};

typedef enum
{
    usNormal,usShift,usCaps,usCapsShift
} keyboard_layout;
#endif //_KEYBOARD_H_
