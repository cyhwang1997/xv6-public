#include "types.h"
#include "user.h"
#include "syscall.h"

void
cy_test(void)
{
//  int i, pid;
  int pid;
  sematest(0);


//  for (i = 0; i < 10; i++) {
    pid = fork();
//    if (!pid)
//      break;
//  }

  if (pid) {
    sleep(200);
    while (wait() != -1)
      ;
    sematest(1);
    printf(1, "final %d\n", sematest(2));
  }
  else {
    printf(1, "child %d: value %d\n", pid, sematest(1));
    printf(1, "child %d: value %d\n", pid, sematest(2));
    exit();
  }

/*  int pid1;
  pid1 = fork();
  if (pid1 == 0)
    for(;;)
      ;
  else {
    printf(1, "[CYDBG] pid1: %d\n", pid1);
    if (sematest(0) == 0)
      printf(1, "[CYDBG] initsema passed\n");
    else
      printf(2, "[CYDBG] initsema failed\n");

    if (sematest(1) == 1)
      printf(1, "[CYDBG] upsema passed\n");
    else
      printf(2, "[CYDBG] upsema failed\n");

    if (sematest(2) == 2)
      printf(1, "[CYDBG] downsema passed\n");
    else
      printf(2, "[CYDBG] downsema failed\n");
  }*/
  exit();
}

int
main(int argc, char *argv[]) 
{
  printf(1, "[CYDBG] test\n");

  cy_test();
  exit();
}
