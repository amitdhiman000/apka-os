#include <kpaging.h>
#include <ktypes.h>
#include <stdio.h>


/* functions defined in registers.asm file */
#if 0
extern uint32_t read_cr0(void);
extern uint32_t read_cr3(void);
extern void write_cr0(uint32_t);
extern void write_cr3(uint32_t);
#else
extern pointer_t read_cr0(void);
extern pointer_t read_cr3(void);
extern void write_cr0(pointer_t);
extern void write_cr3(pointer_t);
#endif

static uint32_t g_page_directory[1024] __attribute__((aligned(4096)));
static uint32_t first_page_table[1024] __attribute__((aligned(4096)));


void paging_install(void)
{
    //set each entry to not present
    for (uint32_t i = 0; i < 1024; ++i)
    {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        g_page_directory[i] = 0x2;
    }

    //we will fill all 1024 entries in the table, mapping 4 megabytes
    for (uint32_t i = 0; i < 1024; ++i)
    {
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes ;)
        // attributes: supervisor level, read/write, present.
        first_page_table[i] = (i * 0x1000) | 0x3;
    }

    // attributes: supervisor level, read/write, present
    g_page_directory[0] = ((uint32_t)first_page_table) | 0x3;


    // write_cr3, read_cr3, write_cr0, and read_cr0 all come from the assembly functions
    write_cr3(g_page_directory); // put that page directory address into CR3
    write_cr0((pointer_t)((uint32_t)read_cr0() | 0x80000000)); // set the paging bit in CR0 to 1
    printf("pagging initialized...\n");
}