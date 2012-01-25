//
// isr.c -- High level interrupt service routines and interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
//

#include "common.h"
#include "isr.h"
#include "monitor.h"
#include "hports.h"

#define INTERRUPT_ENTRY_NUMS
isr_t interrupt_handlers[INTERRUPT_ENTRY_NUMS];



// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
	monitor_write("recieved interrupt: ");
	monitor_write_dec(regs.int_no);
	monitor_put('\n');
}


// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
	// Send an EOI (end of interrupt) signal to the PICs.
	// If this interrupt involved the slave.
	if (regs.int_no >= 40)
	{
		// Send reset signal to slave.
		outb(PIC_SLAVE_CMD_PORT, PIC_EIO_CMD);
	}
	// Send reset signal to master. (As well as slave, if necessary).
	outb(PIC_MASTER_CMD_PORT, PIC_EIO_CMD);

	if (interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}

void register_interrupt_handler(u8int n, isr_t handler)
{
	  interrupt_handlers[n] = handler;
}
