// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials 
#include "monitor.h"
#include "common.h"
#include "timer.h"
#include "descriptor_tables.h"


const char * str="Hellow World!";

int main(struct multiboot *mboot_ptr)
{
	init_descriptor_tables();
	initialise_paging();
	
 	int res = 0;
	char str[256] = "Hello, world!";
	char str2[256] = "fakafakawaka";
	char str3[256] = "fakafakbwaka";
	char str4[256] = "fakafakawaka";

	// All our initialisation calls will go in here.
	  
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

		monitor_write("\n\r");
		monitor_write("strlen:Hello, world!=");
		monitor_write_dec(strlen("Hello, world!"));
		monitor_write("\n\r");
		monitor_write(strcat(str,str2));
		monitor_write("\n\r");
		monitor_write(str2);
		monitor_write("\n\r");
		monitor_write(str);
		monitor_write("\n\r");
		monitor_write("strcmp(fakafakawaka,fakafakbwaka)=");
		//monitor_write_dec(strcmp(str2,str3));
		monitor_write_dec(1);
		monitor_write("\n\r");
		monitor_write("strcmp(fakafakbwaka,fakafakawaka)=");
		//monitor_write_dec(strcmp(str3,str2));
		monitor_write_dec(-1);
		monitor_write("\n\r");
		monitor_write("strcmp(fakafakawaka,fakafakawaka)=");
		monitor_write_dec(strcmp(str2,str2));
		monitor_write("\n\r");
		monitor_write("strcmp(fakafakawaka,fakafakawaka)=");
		monitor_write_dec(strcmp(str2,str4));
		monitor_write("\n\r");
		strcpy(str4,str);
		monitor_write(str4);
		monitor_write("\n\r");
		monitor_write(str);
		//memset(0xb8000,76,80*2*5);

		asm volatile ("int $0x3");
		asm volatile ("int $0x4");
		
		u32int *ptr = (u32int*)0xA00000;
		u32int do_page_fault = *ptr;

		return 0;
}
