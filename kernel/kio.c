#include <kio.h>


#define IN(port) ({ \
		byte_t v; \
		__asm__ __volatile__ ("inb %%dx, %%al" \
				: "=a" (v) : "d" (port)); \
		v; \
})

#define OUT(port, value) \
		__asm__ __volatile__ ("outb %%al, %%dx" :: "a" (value), \
					"d" (port))


const byte_t inportb(const uint16_t port)
{
    return IN(port);
}

void outportb(const uint16_t port, const byte_t val)
{
    OUT(port, val);
}

#if 0
byte_t inportb(uint16_t _port)
{
    byte_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb(uint16_t _port, byte_t _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
#endif