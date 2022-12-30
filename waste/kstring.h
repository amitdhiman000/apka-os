#ifndef __KSTRING_H__
#define __KSTRING_H__

#include <ktypes.h>



extern void itoa(__uint64, uint8_t *, char);
extern uint32_t strlen(const char *);
extern uint16_t strcmp(const char *, const char *);
extern uint16_t strncmp(const char *, const char *, uint32_t);
extern char *strcat(char *, const char *);
extern char *strncat(char *, const char*, uint32_t);
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char*, uint32_t);

#endif
