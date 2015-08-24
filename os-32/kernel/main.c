#include <system.h>
#include <screen.h>
#include <low_level.h>
#include <malloc.h>
#include <keyboard.h>

void initialize_kernel(struct multiboot_info *mbinfo, uint32_t kernel_end_addr);

void main(struct multiboot_info *mbinfo, uint32_t kernel_end_addr)
{
    initialize_kernel(mbinfo,kernel_end_addr);
    kprintf("Welcome to MikOS II:");
    sti();
    while(1)
    {
        unsigned char temp = Keyboard_ReadNext();
        if(temp != 0)
        {
            kprintf("%c",temp);
        }
    }
}

void initialize_kernel(struct multiboot_info *mbinfo, uint32_t kernel_end_addr)
{
    int i;
    unsigned char buffer[512];
    gdt_init();
    idt_init();
    irq_init();
    isrs_init();
    init_keyboard();
    size_t totalMemory = (mbinfo->low_mem + mbinfo->high_mem + 1024);
    multiboot_memory_map_t *mmap_ptr = (multiboot_memory_map_t*) mbinfo->mmap_addr;
    multiboot_memory_map_t *mmap_end = (multiboot_memory_map_t*) (mbinfo->mmap_addr + mbinfo->mmap_length);
    mm_init(totalMemory,kernel_end_addr);

    while (mmap_ptr < mmap_end)
    {
        if (mmap_ptr->type == MULTIBOOT_MEMORY_AVAILABLE)
        {
            uint32_t region_base_addr = (uint32_t) (mmap_ptr->addr & 0xffffffff);
            uint32_t region_size = (uint32_t) (mmap_ptr->len & 0xffffffff);

            mm_mark_region_unused(region_base_addr, region_size);
        }
        mmap_ptr = (multiboot_memory_map_t*) ((uint32_t) mmap_ptr + mmap_ptr->size + sizeof (uint32_t));
    }

    unsigned int kernelSize = kernel_end_addr - KERNEL_BASE_ADDR;
    mm_mark_region_used(KERNEL_BASE_ADDR, kernelSize + mm_get_bitmap_size());
    irq_install_handler(1,keyboard_handler);

}
