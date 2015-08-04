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
    size_t totalMemory = (mbinfo->low_mem + mbinfo->high_mem + 1024);

    multiboot_memory_map_t *mmap_ptr = (multiboot_memory_map_t*) mbinfo->mmap_addr;
    multiboot_memory_map_t *mmap_end = (multiboot_memory_map_t*) (mbinfo->mmap_addr + mbinfo->mmap_length);
    mm_init(totalMemory,kernel_end_addr);

    while (mmap_ptr < mmap_end) {
    if (mmap_ptr->type == MULTIBOOT_MEMORY_AVAILABLE) {
        uint32_t region_base_addr = (uint32_t) (mmap_ptr->addr & 0xffffffff);
        uint32_t region_size = (uint32_t) (mmap_ptr->len & 0xffffffff);

        mm_mark_region_unused(region_base_addr, region_size);
    }
    mmap_ptr = (multiboot_memory_map_t*) ((uint32_t) mmap_ptr + mmap_ptr->size + sizeof (uint32_t));
    }

    unsigned int kernelSize = kernel_end_addr - KERNEL_BASE_ADDR;
    mm_mark_region_used(KERNEL_BASE_ADDR, kernelSize + mm_get_bitmap_size());

    int *integers[1200];
    //moreCore is called at least once when the first malloc is called as the linked list is not yet created at that point.
    for (int i = 0; i < 513; i++) { //just enought to generate a need for morecore
        integers[i] = malloc(sizeof (int*));
        *integers[i] = i;
    }

    for (int i = 5; i < 10; i++) { // if this is remove moreCore will be called 3 times
        free(integers[i]);
    }

    for (int i = 513; i < 1025; i++) { //should not require more mwmoey because of the freed space
        integers[i] = malloc(sizeof (int*));
        *integers[i] = i;
    }

//you can test where memory is being allocated with this code.
    /*for (int i = 0; i < 1200; i++) {
        kprintf("value: %u", *integers[i]);
    }
    */

    /*uint32_t *p = malloc(sizeof(p));
    kprintf("\tp1: %p\n",p);
    uint32_t *p2 = malloc(sizeof(p2));
    kprintf("p2: %p\n",p2);
      uint32_t *p3 = malloc(sizeof(p3));
    kprintf("p3: %p\n",p3);
        uint32_t *p4 = malloc(sizeof(p4));
        *p4 = 10;
    kprintf("p4: %p\n",p4);
    kprintf("*p4: %u\n",*p4);
        free(p4);
    uint32_t *p5 = malloc(sizeof(p5));
    char* car = malloc((size_t)100);
    kprintf("car: %p\n",car);
    kprintf("p5: %p\n",p5);
    kprintf("*p5: %u\n",*p5);
*/
        while(1);

    }
