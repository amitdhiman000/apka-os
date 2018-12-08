#include <kmain.h>
#include <system.h>
#include <kgdt.h>
#include <kidt.h>
#include <kisrs.h>
#include <kirq.h>
#include <kkbd.h>
#include <ktimer.h>
#include <kconsol.h>
#include <stdio.h>
#include <ktest.h>

void kmain(void *MultibootStructure)
{
	// Kernel execution starts here.
	// 1. Clear the screen 
	ConsolClear();
	SetConsolColor(White, Blue);

	// install the drivers.
	gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    //timer_install();
    keyboard_install();
	sti();

	printf("Welcome Amit Dhiman\n");

	test_konsole();

	// to continue execution other wise system will halt
	for(;;);

	//ConsolClear();
	//reboot();
}
