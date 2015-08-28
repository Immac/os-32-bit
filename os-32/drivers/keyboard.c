#include <keyboard.h>

#define LSHIFT_PRS 42
#define RSHIFT_PRS 54
#define LSHIFT_RLS 42 | 0x80
#define RSHIFT_RLS 54 | 0x80

#define CAPS_LCK_PRS 58
#define CAPS_LCK_RLS 58 |0x80

#define KEYBOARD_LAYOUT_COUNT 4
#define KEYBOARD_BUFFER_SIZE 255

//#define DEBUG_KEYBOARD_HANDLER
#ifdef DEBUG_KEYBOARD_HANDLER
//#define DEBUG_UPDATE_KEYBOARD_LAYOUT
#endif // DEBUG_KEYBOARD_HANDLER
typedef enum LockFlags
{
    CapsLockFlag = 0x01,
    NumLockFlag = 0x02,
    ScrLockFlag = 0x04,
} LockFlags_type;

typedef enum ModifierFlags
{
    RightShiftFlag = 0x01,
    LeftShiftFlag = 0x02,
    RightCtrlFlag = 0x04,
    LeftCtrlFlag = 0x08,
    RightAltFlag = 0x10,
    LeftAltFlag = 0x20,
} ModifierFlags_type;

typedef enum KeyboardLayout
{
    UsNormal,UsShift,UsCaps,UsCapsShift
} KeyboardLayout_type;

struct KeyboardStatus
{
    unsigned char buffer[KEYBOARD_BUFFER_SIZE];
    Queue_type keyboard_queue;
    LockFlags_type lockFlags;
    ModifierFlags_type modifierFlags;
};

unsigned char keyboard_layouts[KEYBOARD_LAYOUT_COUNT][128];
struct KeyboardStatus current_keyboard_data;
KeyboardLayout_type current_layout;

KeyboardLayout_type updateKeyboardLayout();
void actionOnRelease(unsigned char scancode);
void actionOnPress(unsigned char scancode);

void init_keyboard()
{
    current_keyboard_data = (struct KeyboardStatus)
    {
        .lockFlags = NumLockFlag,
         .modifierFlags = 0
    };
    for(int i = 0; i < KEYBOARD_LAYOUT_COUNT; i++)
    {
        current_keyboard_data.buffer[i] = 0;
    }
    Queue_Constructor(&current_keyboard_data.keyboard_queue,current_keyboard_data.buffer,KEYBOARD_BUFFER_SIZE);
    current_layout = UsNormal;
}

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = port_byte_in(0x60);

    if (scancode & 0x80) /*Was key released?*/
    {
        actionOnRelease(scancode);
    }
    else
    {
        actionOnPress(scancode);
        Queue_Enqueue(&current_keyboard_data.keyboard_queue,keyboard_layouts[current_layout][scancode]);

#ifdef DEBUG_KEYBOARD_HANDLER
        kprintf("%c",keyboard_layouts[current_layout][scancode]);
#endif // DEBUG_KEYBOARD_HANDLER
    }
    current_layout = updateKeyboardLayout();
}

KeyboardLayout_type updateKeyboardLayout()
{
    if(current_keyboard_data.modifierFlags & LeftShiftFlag || current_keyboard_data.modifierFlags & RightShiftFlag)
    {
        if(current_keyboard_data.lockFlags & CapsLockFlag)
        {
#ifdef DEBUG_UPDATE_KEYBOARD_LAYOUT
            kprintf("usCapsShift");
#endif // DEBUG_UPDATE_KEYBOARD_LAYOUT
            return UsCapsShift;
        }
#ifdef DEBUG_UPDATE_KEYBOARD_LAYOUT
        kprintf("usShift");
#endif // DEBUG_UPDATE_KEYBOARD_LAYOUT
        return UsShift;
    }
    if(current_keyboard_data.lockFlags & CapsLockFlag)
    {
#ifdef DEBUG_UPDATE_KEYBOARD_LAYOUT
        kprintf("usCaps");
#endif // DEBUG_UPDATE_KEYBOARD_LAYOUT
        return UsCaps;
    }
#ifdef DEBUG_UPDATE_KEYBOARD_LAYOUT
    kprintf("usNormal");
#endif // DEBUG_UPDATE_KEYBOARD_LAYOUT
    return UsNormal;
}

void actionOnRelease(unsigned char scancode)
{
    switch(scancode)
    {
    case LSHIFT_RLS:
        current_keyboard_data.modifierFlags &= ~LeftShiftFlag;
        break;
    case RSHIFT_RLS:
        current_keyboard_data.modifierFlags &= ~RightShiftFlag;
        break;
    case CAPS_LCK_RLS:
        break;
    default:
        break;
    }
}

void actionOnPress(unsigned char scancode)
{
    switch(scancode)
    {
    case LSHIFT_PRS:
        current_keyboard_data.modifierFlags |= LeftShiftFlag;
        break;
    case RSHIFT_PRS:
        current_keyboard_data.modifierFlags |= RightShiftFlag;
        break;
    case CAPS_LCK_PRS:
        current_keyboard_data.lockFlags ^= CapsLockFlag;
        break;
    default:
        break;
    }
}

unsigned char Keyboard_ReadKey(void)
{

    unsigned char read_key = '\0';
    //puts("Keyboard_ReadKey");
    while(read_key == '\0')
     {
         cli();
         read_key = Queue_Dequeue(&current_keyboard_data.keyboard_queue);
         sti();
     }

     return read_key;
}

unsigned char keyboard_layouts[KEYBOARD_LAYOUT_COUNT][128] =
{
    /*US Normal*/
    {
        255, 27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
        '9', '0', '-', '=', '\b',	/* Backspace */
        '\t',			/* Tab */
        'q', 'w', 'e', 'r',	/* 19 */
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
        254,			/* 29   - Control */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
        '\'', '`',   253,		/* Left shift [42]*/
        '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
        'm', ',', '.', '/',   252,				/* Right shift [54]*/
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
    },
    /*US Shift*/
    {
        255,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
        '(', ')', '_', '+', '\b',	/* Backspace */
        '\t',			/* Tab */
        'Q', 'W', 'E', 'R',	/* 19 */
        'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
        254,			/* 29   - Control */
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
        '\"', '~',   253,		/* Left shift */
        '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
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
    },
    /*US Caps*/
    {
        255, 27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
        '9', '0', '-', '=', '\b',	/* Backspace */
        '\t',			/* Tab */
        'Q', 'W', 'E', 'R',	/* 19 */
        'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
        254,			/* 29   - Control */
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',	/* 39 */
        '\"', '`',   253,		/* Left shift */
        '\\', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
        'M', ',', '.', '/',   252,				/* Right shift */
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
    },
    /*US CapsShift*/
    {
        255,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
        '(', ')', '_', '+', '\b',	/* Backspace */
        '\t',			/* Tab */
        'q', 'w', 'e', 'r',	/* 19 */
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
        254,			/* 29   - Control */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ':',	/* 39 */
        '\"', '~',   253,		/* Left shift */
        '|', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
        'm', '<', '>', '?',   252,				/* Right shift [54]*/
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
    }
};


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
