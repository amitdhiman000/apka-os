/***************************************************************************
 *            stdio.h
 *
 *  Sat Mar 31 07:47:55 2007
 *  Copyright  2007  shainer
 *  Email : shainer@debianclan.org
 *  Standard I/0 header
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

#ifndef __STDIO_H__
#define __STDIO_H__

#define MAX_DIGITS_IN_INTEGER 11

#ifndef NULL
#define NULL void*(0)
#endif

#ifndef EOF
#define EOF (-1)
#endif



extern void putchar(const char ch);
extern int atoi(const char * const str);
extern char *gets(void);
extern int puts(const char * const str);
extern int printf(const char * const fmt, ...);
extern int scanf(const char * const fmt, ...);


#endif /* __STDIO_H__ */
