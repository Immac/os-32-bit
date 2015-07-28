#include <system.h>
#include <screen.h>
#include <low_level.h>

void main(struct multiboot_info *mbinfo, uint32_t kernel_end_addr)
{
    int i;
    unsigned char buffer[512];
    gdt_init();
    idt_init();
    irq_init();
    isrs_init();
}
