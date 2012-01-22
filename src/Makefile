# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

LOCATION?=./

SOURCES:=boot.c main.c common.c monitor.c descriptor_tables.c dt.c
SOURCES:=$(SOURCES:.c=.o)
SOURCES:=$(addprefix $(LOCATION),$(SOURCES))

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
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
