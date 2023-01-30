#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "spinlock.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "semaphore.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

void
initsema(struct semaphore *sema, int initvalue)
{
  sema->value = initvalue;
  sema->head_index = 0;
  sema->tail_index = 0;
  initlock(sema->lock, "semaphore");
  int i;
  for (i = 0; i < NPROC; i++)
    sema->waiters[i] = -1;
  
  /*CYDBG
  cprintf("\n[CYDBG] initsema  sema->value: %d\n", sema->value);
  cprintf("[CYDBG] initsema  sema->head_index: %d\n", sema->head_index);
  cprintf("[CYDBG] initsema  sema->tail_index: %d\n", sema->tail_index);*/
}

int
downsema(struct semaphore *sema)
{
  int ret = 0;
  acquire(sema->lock);
  sema->value--;

  if (sema->value < 0) {
    if (sema->tail_index - sema->head_index  == 64) {
      release(sema->lock);
      return -1;
    }
    sema->waiters[sema->tail_index] = myproc()->pid;
    ret = sema->tail_index++;
    sleep(myproc(), sema->lock);
  }
  /*CYDBG
  cprintf("\n[CYDBG] downsema  sema->value: %d\n", sema->value);
  cprintf("[CYDBG] downsema  sema->head_index: %d\n", sema->head_index);
  cprintf("[CYDBG] downsema  sema->tail_index: %d\n", sema->tail_index);*/
  release(sema->lock);
  return ret;
}

int
upsema(struct semaphore *sema)
{
  struct proc *p;
  acquire(sema->lock);
  sema->value++;
  if (sema->value <= 0) {
    int pid;
    pid = sema->waiters[sema->head_index];
    sema->head_index++;
  
    acquire(&ptable.lock);
    for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
      if (p->pid == pid)
        break;
    }
    release(&ptable.lock);
    wakeup(p);
  }
  /*CYDBG
  cprintf("\n[CYDBG] upsema  sema->value: %d\n", sema->value);
  cprintf("[CYDBG] upsema  sema->head_index: %d\n", sema->head_index);
  cprintf("[CYDBG] upsema  sema->tail_index: %d\n", sema->tail_index);*/

  release(sema->lock);

  return sema->value;
}
