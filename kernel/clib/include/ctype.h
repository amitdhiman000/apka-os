/* Functions related to character handling
 * Dreamos
 * ctype.h
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * Autrice: shainer
 * Data: 26 gennaio 2006
 */

#ifndef __CTYPE_H__
#define __CTYPE_H__

#define OFFSET 32 /* Distance from a uppercase character to the correspondent lowercase in ASCII */

extern int isdigit(int c);
extern int isalpha(int c);
extern int isalnum(int c);
extern int isxdigit(int c);
extern int islower(int c);
extern int isupper(int c);
extern int isspace(int c);
extern int iscntrl(int c);
extern int ispunct(int c);
extern int tolower(int c);
extern int toupper(int c);

#endif /* __CTYPE_H__ */
