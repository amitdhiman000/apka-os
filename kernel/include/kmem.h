#ifndef __KMEM_H__
#define __KMEM_H__

#include <ktypes.h>

extern void *memcpy(void *dest, const void *src, __uint32 n);
extern void *memset(void *s, __uint16 c, __uint32 n);
extern void *memsetw(void *s, __uint16 c, __uint32 n);
extern void *memsetdw(void *s, __uint16 c, __uint32 n);


#endif
