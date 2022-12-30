#ifndef __KMEM_H__
#define __KMEM_H__

#include <ktypes.h>

extern void *memcpy(void *dest, const void *src, uint32_t n);

extern void *memmove(void *dest, const void *src, uint32_t n);

extern void *memset(void *dest, uint8_t c, uint32_t n);

extern void *memsetw(void *dest, uint16_t c, uint32_t n);

extern void *memsetdw(void *dest, uint32_t c, uint32_t n);


#endif /* __KMEM_H__ */
