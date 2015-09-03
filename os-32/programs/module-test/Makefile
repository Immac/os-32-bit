# Automatically expand to a list of existing files that
# match the patterns
C_SOURCES = $(wildcard kernel/*.c drivers/*.c util/*.c *.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h util/*.h *.h)
OBJ = ${C_SOURCES:.c=.o}
INCLUDE = -Ikernel/ -Idrivers/ -Iutil/

C_FLAGS = -O1 -nostdinc -nostdlib -ffreestanding -fno-stack-protector -std=gnu99 -m32
CC = gcc
# CC = ~/develop/llvm/bin/clang

all: program

# Link kernel object files into one binary , making sure the
# entry code is right at the start of the binary .
program : main.o ${OBJ}
	ld -m elf_i386 -T user.ld --entry main -o $@ $^

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

# Disassemble our kernel - might be useful for debugging .
kernel_elf.asm: kernel.elf
	objdump -M intel -S $< > $@
