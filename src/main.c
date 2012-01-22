// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials 
#include "monitor.h"
#include "common.h"


const char * str="Hellow World!";

int main(struct multiboot *mboot_ptr)
{
	  // All our initialisation calls will go in here.
	  
		monitor_clear();
		monitor_write("Hello, world!\n\r");
		monitor_write_hex(0xbadacacd);
		monitor_write("\n\r");
		monitor_write_dec(0xbadacacd);
		monitor_write("\n\r");
		monitor_write_dec(1234567890);

		memcpy(0xb8000+80*2*5,0xb8000,80*2*5);


	
		return 0xDEADBABA;
}
