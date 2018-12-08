#ifndef __KGDT_H__
#define __KGDT_H__

#include <ktypes.h>

/* Defines a GDT entry. We say packed, because it prevents the
*  compiler from doing things that it thinks is best: Prevent
*  compiler "optimization" by packing */
typedef struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
typedef struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;


extern void gdt_install(void);
extern void gdt_set_gate(int num, pointer_t base, uint64_t limit, byte_t access, byte_t gran);
/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */


#endif /* __KGDT_H__ */
