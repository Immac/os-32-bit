#include "read-string.h"


typedef enum SpecialCharacters
{
    Backspace = 0x08,
    Enter = 0x0D,
    Space = 0x20
} SpecialCharacters_type;
/**
*   \param r->ebx The buffer that will be written to.
*   \param r->ecx The size of the buffer that will be written to.
*/
void Osapi_ReadString(struct regs* r)
{
    char *buffer = (char *)r->ebx;
    unsigned int buffer_size = (unsigned int)r->ecx;
    unsigned char current_char = Keyboard_ReadKey();
    int i = 0;
    do
    {
        switch(current_char)
        {
        case Backspace:
            i = Math_Max(0,--i);
            //kprintf("%c",Backspace);
            //kprintf("%c",Space);
            //kprintf("%c",Backspace);
            buffer[i] = Space;
            break;
        case Enter:
            current_char = '\n';
            buffer[i] = current_char;
            //kprintf("%c",Enter);
            i++;
            break;
        default:
            buffer[i] = current_char;
            kprintf("%c",current_char);
            i++;
        }

        current_char = Keyboard_ReadKey();
    } while(current_char != '\n' && i < buffer_size - 1);
    buffer[buffer_size] = '\0';
}

