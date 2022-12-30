#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <stddef.h>
#include <ktypes.h>

typedef enum {
    UNARY = 1,
    BINARY = 2,
    OCTAL = 8,
    DECIMAL = 10,
    HEXADECIMAL = 16,
} numbers_base_t;

extern uint32_t ntos(char * const str, int32_t num, numbers_base_t base);


#endif /* __NUMBER_H__ */