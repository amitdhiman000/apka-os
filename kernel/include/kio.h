#ifndef __KIO_H__
#define __KIO_H__

#include <ktypes.h>

extern const byte_t inportb(const uint16_t port);
extern void outportb(const uint16_t port, const byte_t val);

#endif /* __KIO_H__ */
