#include <kmain.h>
#include <system.h>
#include <kgdt.h>
#include <kidt.h>
#include <kisrs.h>
#include <kirq.h>
#include <kkbd.h>
#include <kmouse.h>
#include <kpaging.h>
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
	//paging_install();


	//timer_install();
	keyboard_install();
	mouse_install();

	// Enable intrupts
	sti();

	printf("Welcome Amit Dhiman\n");

	int count = printf("Amit %s %s %c : %x\n", "Kumar", "Dhiman", '#', 102);

	printf("count is : %d", count);

	// console test cases.
	test_konsole();

	// to continue execution other wise system will halt
	for(;;);

	//ConsolClear();
	//reboot();
}
