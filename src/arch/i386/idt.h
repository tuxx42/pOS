#include <stdint.h>

#define GRAN_64_BIT_MODE (1 << 5)
#define GRAN_32_BIT_MODE (1 << 6)
#define GRAN_4KIB_BLOCKS (1 << 7)

struct idt_entry {
	uint16_t offset_1;	// offset bits 0..15
	uint16_t selector;	// a code segment selector in GDT or LDT
	uint8_t zero;		// unused, set to 0
	uint8_t type_attr;	// type and attributes, see below
	uint16_t offset_2;	// offset bits 16..31
};

#define IDT_ENTRY(base, limit, access, granularity) \
	{ (limit) & 0xFFFF,					/* limit_low */ \
	  (base) >> 0 & 0xFFFF,					/* base_low */ \
	  (base) >> 16 & 0xFF,					/* base_middle */ \
	  (access) & 0xFF,					/* access */ \
	  ((limit) >> 16 & 0x0F) | ((granularity) & 0xF0),	/* granularity */ \
	  (base) >> 24 & 0xFF,					/* base_high */ }
