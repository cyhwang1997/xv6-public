#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  mkdir("/a");
  chdir("/a");
  chdir("/a");
  printf(1, "TEST PASSED\n");
  exit();
}
