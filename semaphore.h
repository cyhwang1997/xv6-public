struct semaphore {
  int value;
  int head_index;
  int tail_index;
  int waiters[64];
  struct spinlock *lock;
};

void initsema(struct semaphore *sema, int initvalue);
int downsema(struct semaphore *sema);
int upsema(struct semaphore *sema);
