#include <kmem.h>
#include <ktypes.h>

/*******************
 * memory functions
 *******************/


/* memcpy()
 * copies n bytes from src to dest
 */
void *memcpy(void *dest, const void *src, uint32_t n)
{
	uint8_t *to = (uint8_t*)dest;
	uint8_t *from = (uint8_t*)src;

	while (n-- > 0)
		*(to++) = *(from++);
	return dest;
}

/* memmove()
* copies n bytes from src to destination, take care overlapping.
*/
void *memmove(void * dest, const void *src, uint32_t count)
{
	register uint8_t *to;
	register uint8_t *from;

	if ( count > 0 )
	{
		if (dest <= src)
		{
			to = (uint8_t *) dest;
			from = (uint8_t *) src;

			while (count--)
				*(to++) = *(from++);
		}
		else
		{
			to = (uint8_t *) dest + count;
			from = (uint8_t *) src + count;

			while (count--)
				*(--to) = *(--from);
		}
	}
	return dest;
}

/* memset()
 * fills the first n bytes of s with the constant
 * byte c
 */

void *memset(void *s, uint8_t c, uint32_t n)
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

void *memsetdw(void *s, uint32_t c, uint32_t n)
{
	uint32_t *to = (uint32_t*) s;

	while (n-- > 0)
		*(to++) = c;
	return s;
}
