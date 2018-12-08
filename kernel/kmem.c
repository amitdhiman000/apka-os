#include <kmem.h>

/*******************
 * memory functions
 *******************/


/* memcpy()
 * copies n bytes from src to dest
 */
void *memcpy(void *dest, const void *src, uint32_t n)
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

void *memset(void *s, uint16_t c, uint32_t n)
{
	uint8_t *to = (uint8_t*) s;

	while (n-- > 0)
		*(to++) = c;
	return s;
}



void *memsetw(void *s, uint16_t c, uint32_t n)
{
	uint16_t *to = (uint16_t*) s;

	while (n-- > 0)
		*(to++) = c;
	return s;
}

void *memsetdw(void *s, uint16_t c, uint32_t n)
{
	uint32_t *to = (uint32_t*) s;

	while (n-- > 0)
		*(to++) = c;
	return s;
}
