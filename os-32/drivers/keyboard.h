#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <../kernel/low_level.h>
#include <../kernel/system.h>
#include <screen.h>

void keyboard_handler(struct regs *r);
struct keyboard_status
{
    unsigned char buffer[255];
    unsigned int start;
    unsigned int current;
    unsigned char lock_flags;
    unsigned char modifier_keys_flags;
};
#endif //_KEYBOARD_H_
