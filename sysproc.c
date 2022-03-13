#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
extern uint rseed;
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int 
sys_settickets(int pid, int n_tickets)
{
  int pd, n;
  if(argint(0, (int*)&pd) < 0 || argint(1, (int*)&n) < 0) {
    return -1;
  }
  if(pd < 1 || n < 0) {
    return -1;
  }
  //acquire(&ptable.lock);
  //for(p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    //if(p->pid == pd) {
    //  p->tickets = n;
   // }
  //}
  //release(&ptable.lock);
  set(pd, n);
  return 0;
}

void 
sys_srand(uint seed)
{
  int s;
  if(argint(0, &s) < 0) {
    //return -1;
  }
  rseed = s;
  //return 0;
}

int 
sys_getpinfo(void) //struct pstat *)
{
  //struct pstat *x;
  //if(argptr(0, (void*)&x, sizeof(*x) < 0)) {
  //  return -1;
  //}
  cprintf("%s", "asdasdasd");
  return 0;
}
