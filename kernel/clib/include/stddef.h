/*
 * Dreamos
 * stddef.h
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
  * Autore Ivan Gualandri
  * Prima versione: 27/10/2003
  * Contiene le definizioni di alcuni tipi di dato :D
  */

#ifndef __STDDEF_H__
#define __STDDEF_H__

#include <ktypes.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef EOF
#define EOF (-1)
#endif

#define BUFSIZ 512

#define KERNEL_SIZE 0x200

typedef uint32_t size_t;

#endif /* __STDDEF_H__ */
