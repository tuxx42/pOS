#include <stdint.h>
#include "gdt.h"

struct gdt_entry gdt[] = {
	/* 0x00: Null segment */
	GDT_ENTRY(0, 0, 0, 0),

	/* 0x08: Kernel Code Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0x9A, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x10: Kernel Data Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0x92, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x18: User Code Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0xFA, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x20: User Data Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0xF2, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),
};

uint16_t gdt_size_minus_one = sizeof(gdt) - 1;
