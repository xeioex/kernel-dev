#include "monitor.h"

#define PANIC(str) do{ monitor_write("PANIC:"); monitor_write(str); monitor_write("\n");asm volatile ("hlt"); } while(0)
