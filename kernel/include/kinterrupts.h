#ifndef __KINTERRUPTS_H__
#define __KINTERRUPTS_H__

#include <ktypes.h>

#define GATE_DEFAULT 0x8E00

/* definitions for PIC operations */
#define PIC1 0x20
#define PIC2 0xA0
#define ICW1 0x11
#define ICW4 0x01

#define ENABLE_NMI 0x00
#define DISABLE_NMI 0x80


#define in(port) ({ \
		byte_t v; \
		__asm__ __volatile__ ("inb %%dx, %%al" \
				: "=a" (v) : "d" (port)); \
		v; \
})

#define out(port, value) \
		__asm__ __volatile__ ("outb %%al, %%dx" :: "a" (value), \
					"d" (port))


/* prototypes */
void put_handler(uint32_t, pointer_t, uint16_t);
void init_pics(int32_t, int32_t);
void send_eoi(int32_t);

#endif /* __KINTERRUPTS_H__ */