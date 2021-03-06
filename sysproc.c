#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
sys_getparentid(void){
  return getparentid();
}

int
sys_getchildren(void){
  int * child_pids;
  
  if (argptr(0 ,(void*)&child_pids , sizeof(int)*64) != 0)
    return -1;
  getchildren(child_pids);
  return 0;
}

int 
sys_getsyscallcounter(void){
  
  int pid;
  
  if(argint(0, &pid) < 0){
    cprintf("%d:\n", pid);
    return -1;
  }  
  return getsyscallcounter(pid);  
};

int 
sys_setpriority(void){

  int prtority;

  if(argint(0, &prtority) < 0)
    return -1;

  return setpriority(prtority);
}

int
sys_changepolicy(void){
  int policy;

  if(argint(0, &policy) < 0)
    return -1;
  changepolicy(policy);
  
  return 0; 
}

int
sys_setqueue(void){
  int pid,q;

  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &q) < 0)
    return -1;  

  setqueue(pid, q);

  return 0;
}

int 
sys_waitandgetmetrics(void){
  metrics *m;
  if (argptr(0,(void*)&m , sizeof(*m)))
    return -1;
  return waitandgetmetrics(m);
}