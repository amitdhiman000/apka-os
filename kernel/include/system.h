#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define lock cli
#define unlock sti

/* prototypes */
void enable_nmi(void);
void disable_nmi(void);

void cli(void);
void sti(void);
void hlt(void);
void reboot(void);
void halt(void);

#endif
