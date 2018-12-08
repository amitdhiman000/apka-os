#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define lock cli
#define unlock sti

/* prototypes */
extern void enable_nmi(void);
extern void disable_nmi(void);

extern void cli(void);
extern void sti(void);
extern void hlt(void);
extern void reboot(void);
extern void halt(void);

#endif /* __SYSTEM_H__ */
