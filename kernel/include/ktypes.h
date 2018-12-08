#ifndef __KTYPES_H__
#define __KTYPES_H__

#if __x86_64__

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef unsigned char byte_t;

typedef signed short int int16_t;
typedef unsigned short int uint16_t;

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef signed long int int64_t;
typedef unsigned long int uint64_t;

typedef void* pointer_t;

#else /* __x86_64__ */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef unsigned char byte_t;

typedef signed short int int16_t;
typedef unsigned short int uint16_t;

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

typedef void* pointer_t;

#endif /* __x86_64__ */

#endif /* __KTYPES_H__ */
