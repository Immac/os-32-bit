#include <system.h>
#include <screen.h>
#include <low_level.h>
#include <malloc.h>

void main(struct multiboot_info *mbinfo, uint32_t kernel_end_addr)
{
    int i;
    unsigned char buffer[512];
    gdt_init();
    idt_init();
    irq_init();
    isrs_init();

    int *hola = (int *)malloc(sizeof(int));
    int *hello = (int *)malloc(sizeof(int));
    *hola = 5;


        for (int i = 0; i < *hola; i++) {
            puts("hola");
        }
        puts("\n");
        //free(hola);
        hello = (int *)malloc(sizeof(int));
        *hello = 10;
        for (int j = 0; j < *hello; j++) {
            puts("hello");
        }
        free(hello);
        free(hola);
        puts("\n");
        hello = (int *)malloc(sizeof(int));
        *hello = 3;
        for (int j = 0; j < *hello; j++) {
            puts("konnichiwa");
        }
        puts("\n");
        puts("adios");
        while(1);
    }
