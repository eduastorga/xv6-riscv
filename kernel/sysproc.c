#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if(t == SBRK_EAGER || n < 0) {
    if(growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if(addr + n < addr)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// T1: implementaciones
uint64
sys_getppid(void) {
  struct proc *p = myproc();
  if (p->parent)
    return p->parent->pid;
  return -1;
}

uint64
sys_getancestor(void) {
  int n = 0;
  // En xv6, argint no retorna un int; solo llena la variable.
  argint(0, &n);
  if (n < 0) return -1;

  struct proc *p = myproc();
  while (n-- > 0) {
    if (p->parent == 0) return -1;
    p = p->parent;
  }
  return p->pid;
}

// --- T2: Lottery Scheduling ---
#include "param.h"
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "proc.h"

// syscall: settickets(int n)
uint64
sys_settickets(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;  // error si no se puede leer argumento

  if(n < 1)
    return -1;  // no se aceptan tickets menores a 1

  struct proc *p = myproc();
  acquire(&p->lock);
  p->tickets = n;  // actualiza la cantidad de tickets
  release(&p->lock);

  return 0;
}

// syscall: getpinfo(int *out)
uint64
sys_getpinfo(void)
{
  uint64 user_addr; // dirección de memoria en espacio de usuario

  if(argaddr(0, &user_addr) < 0)
    return -1;

  struct proc *p = myproc();
  int value = p->cpu_slices;  // cuántas veces fue elegido por el scheduler

  if(copyout(p->pagetable, user_addr, (char *)&value, sizeof(int)) < 0)
    return -1;

  return 0;
}

