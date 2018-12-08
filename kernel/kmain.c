#include <kmain.h>

void kmain(void *MultibootStructure)
{
	
	//string s="This is the Operating System Coded By \nAmit Dhiman\t CSE\t NIT Hamirpur (H.P.)";
	// kernel start executing from here  
	// 1. Clear the screen 
	
	ConsolClear();
	SetConsolColor(White,Blue);
	gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    //timer_install();
    keyboard_install();
	sti();
	//char x;
	//int i;
	//ConsolWriteChar(x);
	//scanf("%d",&i);
	string s;
	ConsolWriteString("Hello");
	s=gets();
	printf("%s",s);
	//char *ch=gets();
	//ConsolWriteString(ch);
	//printf("%s",ch);
	//ConsolWriteString(ch);
	printf("Amit");


	// to continue execution other wise system will halt
	for(;;);
	//ConsolClear();
	//reboot();
}
