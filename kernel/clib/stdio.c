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

#include <kconsol.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <kkbd.h>

#define LEFT 1
#define RIGHT 0

extern upoint ConsolCursor;
extern upoint ConsolSize;
extern __uint8 *VideoRam;
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
	* */
}

int puts (char *s)
{
	ConsolWriteString(s);
	return 1;
	}

/*
 * Convert a string to an integer
 */
int atoi(const char *nptr)
{
  int base=1;
  int res=0;
  int i;

  /* Make sure all chars are numbers */
  for (i=0; *(nptr+i); ++i) {
    if(!isdigit(*(nptr+i)))
      return -1;
  }

  i=0;
  while(nptr[++i])
    base *= 10;

  /* Actual conversion. It works like this: for example, 123 is obtained with
   1*100 + 2*10 + 3*1 */
  for (i=0; *(nptr+i); ++i ) {
    res += ((int)nptr[i] - 48) * base;
    base /= 10;
  }

  return res;
}

/*
 * No words...
 */
int printf (const char *format, ...)
{
    va_list ap;
    char current[255]; // maybe this size will be changed
    char *cur_p = &current[0]; // pointer to the previous array
    int cursize = 0;
    int ishex = 0;

    short int direction=RIGHT;
    short int width=0;
    char field[5];
    int len=0;
    int i=0;

    /* Start variabile argument's list */
    va_start (ap, format);

    while (*format) {

        /* % marks a specific */
	if (*format == '%') {
	    format++;

            /* The field width is to be written to left */
	    if (*format == '-') {
		direction=LEFT;
		format++;
	    }

            /* Take field width if present and convert it to an int */
	    if (isdigit (*format) == 1) { // precisione di campo
		while (isdigit(*format))
		    field[i++] = *format++;
                field[i] = '\0';
		width = atoi (field);
	    }

	    /* Some data type aren't supported yet
             * In the future we will fix this */
	    if (*format == 's')
		cur_p = va_arg (ap, char *);
	    if (*format == 'd' || *format == 'i') {
		int varint = va_arg (ap, int);
		kntos (cur_p, varint, 10);
	    }
	    if (*format == 'u') {
		unsigned int uint = va_arg (ap, int);
		kntos (cur_p, uint, 10);
	    }
	    if (*format == 'x' || *format == 'X') {
	        int varhex = va_arg (ap, int);
		kntos (cur_p, varhex, 16);
                ishex = 1;
	    }
	    if (*format == 'n')
                kntos (cur_p, len, 10);
	    if (*format == '%')
                ConsolWriteChar('%');

	    cursize = strlen(cur_p);

            /* Actually write the field width */
	    if (direction==LEFT) {
		for(i=1; i<=width; i++)
		    BackSpace();
	    } else {
	    for (i=1; i<=width; i++)
		ConsolWriteChar(' ');
	    }
            /* Print the argument converted to a string */

	    if (ishex != 1) {
	      *(cur_p + cursize) = '\0';
	      ConsolWriteString(cur_p);
	    }
            ishex = 0;
	}
	else
            ConsolWriteChar(*format);

        /* Update values */
	format++;
	direction=RIGHT;
        width=0;
	len++;
	for (i=0; i<255; i++)
            current[i] = 0;
    }
    va_end (ap); // end of arguments
    return len;
}

char getchar (void)
{
	char k=kgetch();
	return k;
	
/*	
    char tmpchar;
    __uint32 loc=(ConsolCursor.X + ConsolCursor.Y*ConsolSize.X)*2;
	for(;;)
	{
		tmpchar=VideoRam[loc];
		if(tmpchar!=0x0)
		return tmpchar;
	}
		while((tmpchar=VideoRam[location])==0x00);
		return tmpchar;
		* */
}

char *gets ()
{
    char *str=0;
    int c;
    int count=0;
 

    do {
			c = getchar();
			if (c=='\n') // Enter key
			{
				break;
			}
			else if (c=='\b' && count>0) //backspace
			{
				count--;
			}
			else
			{
				str[count++] = c;
			}
    } while (count<255);

    str[count] = '\0';
    return str;
}


int scanf (const char *format, ...)
{
    va_list scan;
    char *input;
    int count=0;
    char maxchars[5] = {0};
    int i=0, nmax=0;

    char *s_ptr;
    int *i_ptr;

    va_start (scan, format);

    for (; *format; format++) {

	if (*format == '%') {
	    input = gets();
            count += strlen (input);

            if (isdigit(*++format)) {
              while (isdigit(*format)) {
                maxchars[i++] = *format;
                format++;
              }
              maxchars[i] = '\0';
              nmax = atoi(maxchars);
            }

	    switch (*format) {
	    case 's':
		s_ptr = va_arg (scan, char *);

                if (nmax == 0 || strlen(input) <= nmax)
		  s_ptr = strncpy (s_ptr, input, strlen (input));
                else
                  s_ptr = strncpy (s_ptr, input, nmax);
		break;

	    case 'd':
		i_ptr = va_arg (scan, int *);

                if (nmax != 0 && strlen(input) > nmax)
                  input[nmax] = '\0';
		*i_ptr = atoi(input);
                break;
	    }
	}
    }
    va_end (scan);
    return count;
}




/************* Helper functions ***************/


/* Useful for base conversions */
int binvp[255];
int binlen=0;
char *resulthex = 0;

/*
*
 * Move the number "num" into a string
  */
void kntos(char *buffer,unsigned int num, int base)
{
  int mod;
  char *p, *pbase;

  p = pbase = buffer;

  if (base==16) {
     kntohex (num);
      buffer = resulthex; // da correggere
      ConsolWriteString(buffer);
      goto end;
  }

  if (num == 0)
    *p++ = 48;

  while(num > 0)
  {
    mod = num % base;
    *p++ = mod + 48;
    num = num / base;
  }

  *p-- = 0;
  while(p > pbase)
  {
    char tmp;
    tmp = *p;
    *p = *pbase;
    *pbase = tmp;
    
    p--; pbase++;
  }

 end:
  return;

}






/*
 * Convert a number into an hexadecimal string
 */
void kntohex (unsigned int number)
{
  int a, ct, count;
  int four_bit[4];
  char str[5];
  char hex[255];
  int j=0;
  char hexnum[17] = "0123456789abcdef";

  char *binnum[17];
  binnum[0] = "0000";
  binnum[1] = "0001";
  binnum[2] = "0010";
  binnum[3] = "0011";
  binnum[4] = "0100";
  binnum[5] = "0101";
  binnum[6] = "0110";
  binnum[7] = "0111";
  binnum[8] = "1000";
  binnum[9] = "1001";
  binnum[10] = "1010";
  binnum[11] = "1011";
  binnum[12] = "1100";
  binnum[13] = "1101";
  binnum[14] = "1110";
  binnum[15] = "1111";
  binnum[16] = '\0';


  kdecbin (number);
  binlen--;

 ciclo:
  for (a=0; a<4; a++)
    four_bit[a] = 0;

  /* ciclo per mettere i 4bit in single */
  for (ct=3; binlen>=0 && ct>=0; ct--, binlen--)
    four_bit[ct] = binvp[binlen];

  for (count=0; count<4; count++)
      str[count] = four_bit[count] + '0';
  str[4] = '\0';
  
  /* Fa il confronto
   * Te mi chiederai: ma la strcmp non ce l'abbiamo
   * beh io mi ricordo che nel vecchio dreamos c'era
   * al massimo la rifaccio, non è poi complicata ...
   */
  for (count=0; count<16; count++) {
    if (_kstrncmp (str, binnum[count], 4) == 0)
      hex[j++] = hexnum[count];
  }
    
  /* Se ancora non siamo arrivati alla fine
   * ripete tutto
   */  
  if (binlen>=0) { 
    goto ciclo;
  }
  
  /* Alla fine, hex contiene l'esadecimale, ma al contrario!
   * Indi rovesciamo tutto
   */
  int b;
  for (b=0, --j; j>=0; j--, b++)
    resulthex[b] = hex[j];
  resulthex [b] = '\0';
  // result contiene il risultato di tutte le fatiche :D
}


/* 
 * Convert from decimal to binary by saving in an integer array
 */
void kdecbin (int n)
{
  int temp[255];
  int a=0;

  do {
    temp[a++] = n % 2;
    n /= 2;
  } while (n>0);

  binlen = a;
  int b, j=a;

  /* Reverse the array */
  for (b=0, --j; j>=0; j--, b++)
    binvp[b] = temp[j];
}

