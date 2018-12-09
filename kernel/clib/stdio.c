/***************************************************************************
 *            stdio.c
 *
 *  Sat Mar 31 07:47:55 2007
 *  Copyright  2007  shainer
 *  Email : shainer@debianclan.org
 *  Stdio library
 * ***************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <number.h>

#include <kconsol.h>
#include <kkbd.h>

#define LEFT 1
#define RIGHT 0

/*
 * Print a character
 */
void putchar (char ch)
{
	ConsolWriteChar(ch);
	/*
   	asm ("movl $0x0, %%eax\n"
	"int $80\n\t"
	:: "b" (ch));
	* 
	*/
}

int puts(const char *str)
{
	ConsolWriteString(str);
	return 1;
}

/*
 * Convert a string to an integer
 */
int atoi(const char *str)
{
	if (!str || !str[0]) {
		return 0;
	}

	int sign = 0;
	int res = 0;
	if ('-' == str[0]) {
		sign = 1;
	}

	int i = 0;
	/* Make sure all chars are numbers */
	for (i = sign; str[i]; ++i) {
		if(!isdigit(str[i])) {
			return 0;
		}
	}

	for (i = sign; str[i]; ++i) {
        res = res*10 + str[i] - '0';
	}

	return (sign == 0)? res : (-res);
}

const char getchar(void)
{
	const char k = kgetch();
	return k;
}

char *gets(void)
{
	char ch;
	static char str[256];
	int count = 0;

    do {
		ch = getchar();
		if ('\n' == ch) // Enter key
		{
			break;
		}
		else if ('\b' == ch && count > 0) //backspace
		{
			count--;
		}
		else
		{
			str[count++] = ch;
		}
    } while (count < 255);

    str[count] = '\0';

    return str;
}


int printf(const char * format, ...)
{
	va_list ap;
	char current[255]; // maybe this size will be changed
	char *cur_p = &current[0]; // pointer to the previous array
	int cursize = 0;

	byte_t direction = RIGHT;
	byte_t width = 0;
	char field[5];
	int len = 0;
	int i = 0;

	/* Start variabile argument's list */
	va_start(ap, format);
	while (*format) {
		/* % marks a specific */
		if (*format == '%') {
			format++;

			/* The field width is to be written to left */
			if (*format == '-') {
				direction = LEFT;
				format++;
			}

			/* Take field width if present and convert it to an int */
			if (isdigit(*format)) { // precisione di campo
				while (isdigit(*format)) {
					field[i++] = *format++;
				}
				field[i] = '\0';
				width = atoi(field);
			}

			/** Some data type aren't supported yet
			* In the future we will fix this
			*/
			switch(*format) {
				case 's':
				{
					char *str = va_arg(ap, char *);
					int ii = 0;
					while (str[ii]) {
						cur_p[ii] = str[ii];
						++ii;
					}
					cur_p[ii] = '\0';
					break;
				}

				case 'c':
				{
					char ch = va_arg(ap, char);
					cur_p[0] = ch;
					cur_p[1] = '\0';
					break;
				}

				case 'd':
				case 'i':
				{
					int32_t varint = va_arg(ap, int32_t);
					ntos(cur_p, varint, DECIMAL);
					break;
				}

				case 'u':
				{
					uint32_t uint = va_arg(ap, uint32_t);
					ntos(cur_p, uint, DECIMAL);
					break;
				}

				case 'x':
				case 'X':
				{
					int32_t varhex = va_arg(ap, int32_t);
					ntos(cur_p, varhex, HEXADECIMAL);
					break;
				}

				case 'p':
				{
					pointer_t ptr = va_arg(ap, pointer_t);
					ntos(cur_p, (int32_t)ptr, HEXADECIMAL);
					break;
				}

				case 'l':
				{
					// need to hanadle long
					int32_t varhex = va_arg(ap, int32_t);
					ntos(cur_p, varhex, HEXADECIMAL);
					break;
				}

				case 'f':
				{
					// need to handle float
					break;
				}

				case 'n':
				{
					ntos(cur_p, len, DECIMAL);
					break;
				}

				case '%':
				{
					cur_p[0] = '%';
					cur_p[1] = '\0';
					break;
				}
			}

			cursize = strlen(cur_p);

			/* Actually write the field width */
			if (direction == LEFT) {
				for(i = 0; i < width; ++i) {
					BackSpace();
				}
			} else {
				for (i = 0; i < width; ++i) {
					Space();
				}
			}

			/* Print the argument converted to a string */
			ConsolWriteString(cur_p);
		} else {
			ConsolWriteChar(*format);
		}
		
		/* Update values */
		format++;
		width = 0;
		direction = RIGHT;
		len += cursize;
	}
	va_end(ap); // end of arguments

	return len;
}


int scanf(const char *format, ...)
{
    va_list scan;
    char *input = 0;
    char maxchars[5] = {0};
    
	int i = 0;
	int count = 0;
	int nmax = 0;

    char *s_ptr;
    int *i_ptr;

    va_start(scan, format);
    for (; *format; format++) {
		if (*format == '%') {
			input = gets();
			count += strlen(input);
			if (isdigit(*++format)) {
				while (isdigit(*format)) {
					maxchars[i++] = *format;
					format++;
				}
				maxchars[i] = '\0';
				nmax = atoi(maxchars);
			}

			switch (*format)
			{
				case 's':
				{
					s_ptr = va_arg (scan, char *);
					if (nmax == 0 || strlen(input) <= nmax)
				s_ptr = strncpy (s_ptr, input, strlen (input));
						else
						s_ptr = strncpy (s_ptr, input, nmax);
					break;
				}
				case 'd':
				{
					i_ptr = va_arg(scan, int *);
					if (nmax != 0 && strlen(input) > nmax)
						input[nmax] = '\0';
					*i_ptr = atoi(input);
					break;
				}
			}
		}
    }
    va_end(scan);

    return count;
}
