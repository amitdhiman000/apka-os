#ifndef __KSTRING_H__
#define __KSTRING_H__

#include <ktypes.h>



extern void itoa(__uint64, __uint8 *, char);
extern __uint32 strlen(const char *);
extern __uint16 strcmp(const char *, const char *);
extern __uint16 strncmp(const char *, const char *, __uint32);
extern char *strcat(char *, const char *);
extern char *strncat(char *, const char*, __uint32);
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char*, __uint32);

#endif
