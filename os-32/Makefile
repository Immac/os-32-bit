# Automatically expand to a list of existing files that
# match the patterns
C_SOURCES = $(wildcard kernel/*.c kernel/*/*.c drivers/*.c util/*.c)
HEADERS = $(wildcard kernel/*.h kernel/*/*.h drivers/*.h util/*.h )
OBJ = ${C_SOURCES:.c=.o}
INCLUDE = -Ikernel/ -Idrivers/ -Iutil/

C_FLAGS = -O1 -nostdinc -nostdlib -ffreestanding -fno-stack-protector -std=gnu99 -m32
CC = gcc
# CC = ~/develop/llvm/bin/clang

all: os-image

# Run bochs to simulate booting of our code.
run: all
	#echo "Make sure /media/immac/1788-59D0 is accessible"
	#sudo cp kernel.elf /media/immac/1788-59D01
	bochs -f opsys.bxrc -q

os-image: kernel.elf
	#cat $^ > os-image
	#dd if=os-image of=hd1.img conv=notrunc

	sync
	touch os-image

# Link kernel object files into one binary , making sure the
# entry code is right at the start of the binary .
kernel.elf : kernel/kernel_entry.o ${OBJ}
	ld -m elf_i386 -T link.ld -o $@ $^

%.o : %.c
	${CC} ${INCLUDE} ${C_FLAGS} -c $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -I 'boot/' -o $@

# Clear away some of the generated files .
clean:
	rm -fr *.o *.bin *.dis
	rm -fr kernel/*.o boot/*.bin drivers/*.o
	rm -f kernel.elf
	rm -f os-image

# Disassemble our kernel - might be useful for debugging .
kernel_elf.asm: kernel.elf
	objdump -M intel -S $< > $@
