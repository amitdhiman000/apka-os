#ifndef __KTIMER_H__
#define __KTIMER_H__

#include <kirq.h>
#include <kconsol.h>

extern void timer_wait(int ticks);
extern void timer_install();

#endif
