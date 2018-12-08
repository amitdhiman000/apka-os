#include <kstring.h>

/* itoa()
 * convert an integer into a string
 */
void itoa(__uint64 n, __uint8 *s, char base)
{
	__uint32 i, j,k;
	__int8 tmp[20], digit;

	i = 0;
	do
	{
		j = n;
		n /= base;	/* divide num by base */
		n *= base;	/* multiply num by b to isolate the digit */
		digit = j - n;
		
		/* change the numerical digit to printable ASCII value */
		if(digit <= 9)
		{
			tmp[i] = digit + '0';
		}
		else
		{
			tmp[i] = digit - 0x0A + 'A';
		};
		n /= base;	/* divide num by b again to get to the next digit */
		i++;
	} while(n != 0);
	
	tmp[i] = '\0';	/* add the terminator */
	const char *t=(char *)tmp;
	/* reverse string */
	k=strlen(t);
	j = k - 1;
	for (i = 0; i < k; i++) {
		s[i] = tmp[j];
		j--;
	}
	s[i] = '\0';
}


/*******************
 * string functions
 *******************/

/* strlen() 
 * returns length of a string
 */
__uint32 strlen(const char *s)
{
	__uint32 i=0;
	while (*(s++) != '\0')
		i++;
	return i;
}

/* strncmp()
 * compares first n characters of two strings 
 */
__uint16 strncmp(const char *s1, const char *s2, __uint32 n)
{
	int i = 1;

	for (; *s1 == *s2 && i <= n; s1++, s2++, i++)
		if (i == n)
			return 0;	/* equal */
	return *s1 - *s2;
}

/* strcmp() 
 * compares two strings 
 */
__uint16 strcmp(const char *s1, const char *s2)
{
	for (; *s1 == *s2; s1++, s2++)
		if (*s1 == '\0')
			return 0;	/* equal */
	return *s1 - *s2;
}

/* strcat() 
 * adds src to dest
 */
char *strcat(char *dest, const char *src)
{
	char *s = dest;
	
	for (; *s != '\0'; s++)
		;	/* go through dest until we reach a NUL */

	while (*src != '\0')
		*(s++) = *(src++);
	*s = '\0';
	
	return dest;
}

/* strncat() 
 * adds n characters of src to dest 
 */
char *strncat(char *dest, const char *src, __uint32 n)
{
	char *s = dest;
	
	for (; *s != '\0'; s++)
		;	
	while (*src != '\0' && n-- > 0)
		*(s++) = *(src++);
	*s = '\0';

	return dest;
}

/* strcpy() 
 * copies src to dest
 */
char *strcpy(char *dest, const char *src)
{
	while (*src != '\0')
		*(dest++) = *(src++);
	
	return dest;
}

/* strncpy()
 * copies n characters of src to dest
 */
char *strncpy(char *dest, const char *src, __uint32 n)
{
	const char *s = src;
	char *d = dest;

	while (*s != '\0' && n-- > 0)
		*(d++) = *(s++);

	return dest;
}

/* sprintf() 
 * prints format to str
 */
 
 /*
int sprintf(char *str, const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsprintf(str, format, ap);
	va_end(ap);

	return strlen(str);
}
*/

