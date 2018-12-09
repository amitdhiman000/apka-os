#include <ktypes.h>
#include <system.h>
#include <kinterrupts.h>
#include <kio.h>


#define ENABLE_NMI 0x00
#define DISABLE_NMI 0x80

uint16_t ocw1 = 0xFFFF;	/* short int = 16 bits */

/**********************
 * PIC operations here
 *********************/

/* init_pics()
 * init the PICs and remap them
 */
void init_pics(int pic1, int pic2)
{
	/* send ICW1 */
	outportb(PIC1, ICW1);
	outportb(PIC2, ICW1);

	/* send ICW2 */
	outportb(PIC1 + 1, pic1);	/* remap */
	outportb(PIC2 + 1, pic2);	/* pics */

	/* send ICW3 */
	outportb(PIC1 + 1, 4);	/* IRQ2 -> connection to slave */
	outportb(PIC2 + 1, 2);

	/* send ICW4 */
	outportb(PIC1 + 1, ICW4);
	outportb(PIC2 + 1, ICW4);

	/* disable all IRQs */
	outportb(PIC1 + 1, 0xFF);
	outportb(PIC2 + 1, 0xFF);
}

/* enable_irq()
 * sends command to PIC to enable an IRQ
 */
void enable_irq(int irq)
{
	ocw1 &= ~(1 << irq);	/* enable propriate bit with shifting to left
				   invert the thing to enable the interrupt
				   use AND operation to leave the other bits
				   as they are
				 */
	if (irq < 8)
		outportb(PIC1 + 1, ocw1&0xFF);	/* AND with 0xFF to clear the high 8 
					  	   bits because we send to PIC1
						 */
	else
		outportb(PIC2 + 1, ocw1 >> 8);	/* move high 8 bits to low 8 bits
						   since we send to PIC2
						 */
}

/* disable_irq()
 * sends a command to PIC to disable an IRQ
 */
void disable_irq(int irq)
{
	ocw1 |= (1 << irq);	/* shift left to disable the propriate bit
				   OR to not change the mask
				 */

	if (irq < 8)
		outportb(PIC1 + 1, ocw1&0xFF);	/* AND with 0xFF to clear the
						   high 8 bits since we send to PIC1
						 */
	else
		outportb(PIC2 + 1, ocw1 >> 8);	/* move high 8 bits to low 8 bits since
						   we send to PIC2
						 */
}

void write_nmi(byte_t nmi)
{
	outportb(0x70, nmi);
	inportb(0x71);
}

void enable_nmi(void)
{
	write_nmi(ENABLE_NMI);
}

void disable_nmi(void)
{
	write_nmi(DISABLE_NMI);
}


void NMI_enable(void)
{
	outportb(0x70, inportb(0x70) & 0x7F);
}

void NMI_disable(void)
{
	outportb(0x70, inportb(0x70) | 0x80);
}

/**********************
 * CPU operations here
 *********************/

/* sti() 
 * enable interrupts
 */
void sti(void)
{
	__asm__("sti");
}

/* cli()
 * disable interrupts
 */
void cli(void)
{
	__asm__("cli");
}

/* hlt()
 * halts the CPU
 */
void hlt(void)
{
	__asm__("hlt");
}

void save(void)
{
	/* don't have anything here yet */
	/* Use to save Data when we are shutting down the system */
}

/* halt()
 * halts the CPU 
 */
void halt(void)
{
	/* in fact, we do nothing else than saving
	 * everything that needs to be saved and 
	 * wait until s.o. shuts down the PC 
	 */
	
	cli();
	save();	/* save important things */

	//debug("\nPower down");  /* No reference to this function yet , have to write the defination for this function 
	hlt();	/* wait for shutdown */
}

/* reboot()
 * reboots the CPU
 */
void reboot(void)
{
	byte_t temp;

	cli();
	save();
	
	/* flush the keyboard controller */
	do
	{
		temp = in(0x64);
		if (temp & 1) {
			(void) in(0x60);
			continue;
		}
	} while(temp & 2);

	/* send the CPU reset line */
	outportb(0x64, 0xFE);

	hlt();
}
