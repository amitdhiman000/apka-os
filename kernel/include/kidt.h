#ifndef __KIDT_H__
#define __KIDT_H__
/* Intrrupt Descriptor Table */

#include <kmem.h>

typedef struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;        /* Our kernel segment goes here! */
    uint8_t always0;     /* This will ALWAYS be set to 0! */
    uint8_t flags;       /* Set using the above table! */
    uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;



/* This exists in 'start.asm', and is used to load our IDT */
extern void idt_load(void);
extern void idt_install(void);
extern void idt_set_gate(byte_t num, pointer_t base, uint16_t sel, byte_t flags);


#endif /* __KIDT_H__ */
