#include <kgdt.h>


extern void gdt_flush(void);

/* Our GDT, with 3 entries, and finally our special GDT pointer */
static gdt_entry_t g_gdt_table[3];
gdt_ptr_t g_gdt_ptr;

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, pointer_t base, uint64_t limit, byte_t access, byte_t gran)
{
    uint64_t base_p = (uint64_t)base;
    /* Setup the descriptor base address */
    g_gdt_table[num].base_low = (base_p & 0xFFFF);
    g_gdt_table[num].base_middle = (base_p >> 16) & 0xFF;
    g_gdt_table[num].base_high = (base_p >> 24) & 0xFF;

    /* Setup the descriptor limits */
    g_gdt_table[num].limit_low = (limit & 0xFFFF);
    g_gdt_table[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    g_gdt_table[num].granularity |= (gran & 0xF0);
    g_gdt_table[num].access = access;
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_install(void)
{
    /* Setup the GDT pointer and limit */
    g_gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    g_gdt_ptr.base = (uint32_t)&g_gdt_table;

    /* Our NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Flush out the old GDT and install the new changes! */
    gdt_flush();
}
