// timer.c -- Initialises the PIT, and handles clock updates.
// Written for JamesM's kernel development tutorials.

#include "timer.h"
#include "isr.h"
#include "monitor.h"

#define PIT_DATA_PORT_1 0x40
#define PIT_DATA_PORT_2 0x41
#define PIT_DATA_PORT_3 0x42
#define PIT_CMD_PORT    0x43


#define PIT_CMD_REP_MODE 0x36


u32int tick = 0;

static void timer_callback(registers_t regs)
{
	tick++;
	monitor_write("Tick: ");
	monitor_write_hex(tick);
	monitor_write("\r\n");
}

void init_timer(u32int frequency)
{
	// Firstly, register our timer callback.
	register_interrupt_handler(IRQ0, &timer_callback);

	// The value we send to the PIT is the value to divide it's input clock
	// (1193180 Hz) by, to get our required frequency. Important to note is
	// that the divisor must be small enough to fit into 16-bits.
	u32int divisor = 1193180 / frequency;

	// Send the command byte.
	outb(PIT_CMD_PORT, PIT_CMD_REP_MODE);

	// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	u8int l = (u8int)(divisor & 0xFF);
	u8int h = (u8int)( (divisor>>8) & 0xFF );

	// Send the frequency divisor.
	outb(PIT_DATA_PORT_1, l);
	outb(PIT_DATA_PORT_1, h);
}
