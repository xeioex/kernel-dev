struct gdt_entry_struct
{
	u16int limit_low;           // The lower 16 bits of the limit.
	u16int base_low;            // The lower 16 bits of the base.
	u8int  base_middle;         // The next 8 bits of the base.
	u8int  access;              // Access flags, determine what ring this segment can be used in.
	u8int  granularity;
	u8int  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
	u16int limit;               // The upper 16 bits of all selector limits.
	u32int base;                // The address of the first gdt_entry_t struct.
}
__attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

void init_descriptor_tables();

// A struct describing an interrupt gate.
struct idt_entry_struct
{
	u16int base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
	u16int sel;                 // Kernel segment selector.
	u8int  always0;             // This must always be zero.
	u8int  flags;               // More flags. See documentation.
	u16int base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
	u16int limit;
	u32int base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;


// These extern directives let us access the addresses of our ASM ISR handlers.
#define DECLARE_ISR(n) extern void isr##n()

DECLARE_ISR(0);
DECLARE_ISR(1);
DECLARE_ISR(2);
DECLARE_ISR(3);
DECLARE_ISR(4);
DECLARE_ISR(5);
DECLARE_ISR(6);
DECLARE_ISR(7);
DECLARE_ISR(8);
DECLARE_ISR(9);
DECLARE_ISR(10);
DECLARE_ISR(11);
DECLARE_ISR(12);
DECLARE_ISR(13);
DECLARE_ISR(14);
DECLARE_ISR(15);
DECLARE_ISR(16);
DECLARE_ISR(17);
DECLARE_ISR(18);
DECLARE_ISR(19);
DECLARE_ISR(20);
DECLARE_ISR(21);
DECLARE_ISR(22);
DECLARE_ISR(23);
DECLARE_ISR(24);
DECLARE_ISR(25);
DECLARE_ISR(26);
DECLARE_ISR(27);
DECLARE_ISR(28);
DECLARE_ISR(29);
DECLARE_ISR(30);
DECLARE_ISR(31);


#define DECLARE_IRQ(n) extern void irq##n()

DECLARE_IRQ(0);
DECLARE_IRQ(1);
DECLARE_IRQ(2);
DECLARE_IRQ(3);
DECLARE_IRQ(4);
DECLARE_IRQ(5);
DECLARE_IRQ(6);
DECLARE_IRQ(7);
DECLARE_IRQ(8);
DECLARE_IRQ(9);
DECLARE_IRQ(10);
DECLARE_IRQ(11);
DECLARE_IRQ(12);
DECLARE_IRQ(13);
DECLARE_IRQ(14);
DECLARE_IRQ(15);
