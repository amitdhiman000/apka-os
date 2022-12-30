#ifndef __KISRS_H__
#define __KISRS_H__

/* Interrupt Service Routines */

/* This defines what the stack looks like after an ISR was running */
typedef struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
} regs_t;

typedef void (*isr_handler_t)(regs_t *r);

extern void fault_handler(struct regs *r);
extern void isrs_install(void);

#endif /* __KISRS_H__ */
