#ifndef __KIRQ_H__
#define __KIRQ_H__

#include <kio.h>
#include <kisrs.h>


extern void irq_handler(struct regs *r);
extern void irq_install_handler(int irq, isr_handler_t handler);
extern void irq_uninstall_handler(int irq);
extern void irq_install(void);

#endif /* __KIRQ_H__ */
