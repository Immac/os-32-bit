#include <keyboard.h>


#define SHIFT_FLAG 0x01
#define CTRL_FLAG 0x02
#define ALT_FLAG 0x04

#define CAPS_LOCK_FLAG 0x01
#define NUM_LOCK_FLAG 0x02
#define SCR_LOCK_FLAG 0x04

unsigned char keyboard_us_layout_normal[128];
unsigned char keyboard_us_layout_shift_on[128];

struct keyboard_status keyboard_data;

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = port_byte_in(0x60);

    if (scancode & 0x80) /*Was key released?*/
    {
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        kprintf("%c",keyboard_us_layout_normal[scancode]);
    }
}

unsigned char keyboard_us_layout_normal[128] =
{
    255,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    254,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   253,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   252,				/* Right shift */
  '*',
    251,	/* Alt */
  ' ',	/* Space bar */
    250,	/* Caps lock */
    249,	/* 59 - F1 key ... > */
    248,   247,   246,   245,   244,   243,   242,   241,
    240,	/* < ... F10 */
    239,	/* 69 - Num lock*/
    238,	/* Scroll Lock */
    237,	/* Home key */
    236,	/* Up Arrow */
    235,	/* Page Up */
  '-',
    234,	/* Left Arrow */
    233,
    232,	/* Right Arrow */
  '+',
    231,	/* 79 - End key*/
    230,	/* Down Arrow */
    229,	/* Page Down */
    228,	/* Insert Key */
    227,	/* Delete Key */
    226,   225,   224,
    223,	/* F11 Key */
    222,	/* F12 Key */
    221,	/* All other keys are undefined */
};

unsigned char keyboard_us_layout_shift_on[128] =
{
    255,  27, '!', '@', '#', '$', '%', '^', '', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    254,			/* 29   - Control */
  'A', 'S', 'S', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '\"', '~',   253,		/* Left shift */
 '\|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   252,				/* Right shift */
  '*',
    251,	/* Alt */
  ' ',	/* Space bar */
    250,	/* Caps lock */
    249,	/* 59 - F1 key ... > */
    248,   247,   246,   245,   244,   243,   242,   241,
    240,	/* < ... F10 */
    239,	/* 69 - Num lock*/
    238,	/* Scroll Lock */
    237,	/* Home key */
    236,	/* Up Arrow */
    235,	/* Page Up */
  '-',
    234,	/* Left Arrow */
    233,
    232,	/* Right Arrow */
  '+',
    231,	/* 79 - End key*/
    230,	/* Down Arrow */
    229,	/* Page Down */
    228,	/* Insert Key */
    227,	/* Delete Key */
    226,   225,   224,
    223,	/* F11 Key */
    222,	/* F12 Key */
    221,	/* All other keys are undefined */
};
