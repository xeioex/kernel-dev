// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials 
#include "monitor.h"
#include "common.h"
#include "timer.h"
#include "descriptor_tables.h"
#include "isr.h"

const char * str="Hello World!";

static void keyboard_callback(registers_t regs)
{
	monitor_write("keyboard pressed: ");
	monitor_write("\r\n");
	register_interrupt_handler(IRQ1, keyboard_callback);
}

int main(struct multiboot *mboot_ptr)
{
	// All our initialisation calls will go in here.
	init_descriptor_tables();
	monitor_clear();
	initialise_paging();
//	init_timer(3);

	int res = 0;

	monitor_clear();
	monitor_write(str);
	monitor_write("\n\r");
	monitor_write_hex(0xbadacacd);
	monitor_write_hex(0xbada0000);
	monitor_write("\n\r");
	monitor_write_dec(0xadacacd);
	monitor_write("\n\r");
	monitor_write_dec(1234567890);

	//memcpy(0xb8000+80*2*5,0xb8000,80*2*5);
	//memset(0xb8000,76,80*2*5);

	asm volatile ("int $0x3");

	//u32int *ptr = (u32int*)0x0ffffff;
	//u32int do_page_fault = *ptr;
	

	return 0;
}
