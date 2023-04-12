#include "types.h"
#include "riscv.h"
#include "param.h"
#include "spinlock.h"
#include "defs.h"
#include "sysinfo.h"
#include "proc.h"
#include "memlayout.h"

int
systeminfo(uint64 addr) {
    struct proc *p = myproc();
    struct sysinfo info;

    info.uptime = ticks/10;
    info.totalram = PHYSTOP - KERNBASE;
    info.freeram = freemem();
    info.procs = nproc();

    if(copyout(p->pagetable, addr, (char *)&info, sizeof(info)) < 0) {
        return -1;
    }
    return 0;
}