#include <kmem.h>

/*******************
 * memory functions
 *******************/


/* memcpy()
 * copies n bytes from src to dest
 */
void *memcpy(void *dest, const void *src, __uint32 n)
{
	char *to = (char*) dest, *from = (char*) src;

	while (n-- > 0)
		*(to++) = *(from++);
	return dest;
}

/* memset()
 * fills the first n bytes of s with the constant
 * byte c
 */

void *memset(void *s, __uint16 c, __uint32 n)
{
	__uint8 *to = (__uint8*) s;

	while (n-- > 0)
		*(to++) = c;
	return s;
}



void *memsetw(void *s, __uint16 c, __uint32 n)
{
	__uint16 *to = (__uint16*) s;

	while (n-- > 0)
		*(to++) = c;
	return s;
}

void *memsetdw(void *s, __uint16 c, __uint32 n)
{
	__uint32 *to = (__uint32*) s;

	while (n-- > 0)
		*(to++) = c;
	return s;
}
