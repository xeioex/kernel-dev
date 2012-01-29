#include "monitor.h"

#define PANIC(str) do{ monitor_write("PANIC:"); monitor_write(str); monitor_write("\n");asm volatile ("hlt"); } while(0)
#define BUG(str) do{ monitor_write("BUG:"); monitor_write(str); monitor_write("\n");asm volatile ("hlt"); } while(0)

extern u32int debug_level;

#define DEBUGLEVEL_LODEBUG 5
#define DEBUGLEVEL_DEBUG 4
#define DEBUGLEVEL_INFO 3
#define DEBUGLEVEL_WARNING 2
#define DEBUGLEVEL_ERROR 1


#ifdef KDEBUG
#define LODEBUG(str) if(debug_level>=DEBUGLEVEL_LODEBUG)do{monitor_write("LODEBUG:"); monitor_write(str); monitor_write("\n");}while(0)
#define DEBUG(str) if(debug_level>=DEBUGLEVEL_DEBUG)do{monitor_write("DEBUG:"); monitor_write(str); monitor_write("\n");}while(0)
#define INFO(str) if(debug_level>=DEBUGLEVEL_INFO)do{monitor_write("INFO:"); monitor_write(str); monitor_write("\n");}while(0)
#define WARINING(str) if(debug_level>=DEBUGLEVEL_WARNING)do{monitor_write("WARNING:"); monitor_write(str); monitor_write("\n");}while(0)
#else

#define LODEBUG(str) 
#define DEBUG(str) 
#define INFO(str)
#define WARINING(str) 
#endif /* KDEBUG */
#define ERROR(str) if(debug_level>=DEBUGLEVEL_ERROR)do{monitor_write("ERROR:"); monitor_write(str); monitor_write("\n");}while(0)
