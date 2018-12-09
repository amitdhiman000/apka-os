#include <kidt.h>

extern void idt_load(void);

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
static idt_entry_t g_idt_table[256];
idt_ptr_t g_idt_ptr;
/* Defines an IDT entry */



/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(byte_t num, pointer_t base, uint16_t sel, byte_t flags)
{
    /* The interrupt routine's base address */
    uint64_t base_p = (uint64_t)base;
    g_idt_table[num].base_lo = (base_p & 0xFFFF);
    g_idt_table[num].base_hi = (base_p >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    g_idt_table[num].sel = sel;
    g_idt_table[num].always0 = 0;
    g_idt_table[num].flags = flags;
}

/* Installs the IDT */
void idt_install(void)
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    g_idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    g_idt_ptr.base = (uint32_t)&g_idt_table;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&g_idt_table, 0, sizeof(idt_entry_t) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */


    /* Points the processor's internal register to the new IDT */
    idt_load();
}

