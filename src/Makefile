# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

LOCATION?=./

SOURCES:=boot.o main.o common.o monitor.o descriptor_tables.o dt.o isr.o interrupts.o timer.o kheap.o paging.o debug.o
SOURCES:=$(addprefix $(LOCATION),$(SOURCES))

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -DKDEBUG
LDFLAGS=-TLink.ld -m elf_i386
ASFLAGS=-felf

all: $(SOURCES) link 

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

%.o:%.s
	nasm $(ASFLAGS) $<

%.o:%.c
	$(CC) $(CFLAGS)  -o $@ -c $<
