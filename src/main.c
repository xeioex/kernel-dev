// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials 
#include "monitor.h"
#include "common.h"


const char * str="Hellow World!";

int main(struct multiboot *mboot_ptr)
{
	int res;
	char str[256] = "Hello, world!";
	char str2[256] = "fakafakawaka";
	char str3[256] = "fakafakbwaka";
	char str4[256] = "fakafakawaka";

	// All our initialisation calls will go in here.
	  
		monitor_clear();
		monitor_write(str);
		monitor_write("\n\r");
		monitor_write_hex(0xbadacacd);
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

		
	
		return 0xDEADBABA;
}
